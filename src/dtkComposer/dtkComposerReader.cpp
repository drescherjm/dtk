/* dtkComposerReader.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:41:08 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 19 15:05:19 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 430
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerFactory.h"
#include "dtkComposerGraph.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeReal.h"
#include "dtkComposerReader.h"
#include "dtkComposerScene.h"
#include "dtkComposerScene_p.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerSceneNote.h"
#include "dtkComposerScenePort.h"
#include "dtkComposerStackUtils.h"
#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterProxy.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkCore/dtkGlobal.h>

#include <QtCore>
#include <QtXml>

// /////////////////////////////////////////////////////////////////
// dtkComposerReaderPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerReaderPrivate
{
public:
    bool check(const QDomDocument& document);

public:
    dtkComposerFactory *factory;
    dtkComposerScene *scene;
    dtkComposerGraph *graph;

public:
    QHash<int, dtkComposerSceneNode *> node_map;

public:
    dtkComposerSceneNodeComposite *root;
    dtkComposerSceneNodeComposite *node;

public:
    dtkComposerSceneNodeControl *control;
};

bool dtkComposerReaderPrivate::check(const QDomDocument& document)
{
    return true;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerReader
// /////////////////////////////////////////////////////////////////

dtkComposerReader::dtkComposerReader(void) : d(new dtkComposerReaderPrivate)
{
    d->factory = NULL;
    d->scene = NULL;
    d->root = NULL;
    d->graph = NULL;

    d->control = NULL;
}

dtkComposerReader::~dtkComposerReader(void)
{
    delete d;

    d = NULL;
}

void dtkComposerReader::setFactory(dtkComposerFactory *factory)
{
    d->factory = factory;
}

void dtkComposerReader::setScene(dtkComposerScene *scene)
{
    d->scene = scene;
}

void dtkComposerReader::setGraph(dtkComposerGraph *graph)
{
    d->graph = graph;
}

bool dtkComposerReader::read(const QString& fileName, bool append)
{
    // Setting dom document

    QDomDocument document("dtk");

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly))
        return false;

    if (!dtkIsBinary(fileName)) {

        if (!document.setContent(&file)) {
            file.close();
            return false;
        }

    } else {

        QByteArray c_bytes;
        QDataStream stream(&file); stream >> c_bytes;
        QByteArray u_bytes = QByteArray::fromHex(qUncompress(c_bytes));

        if(!document.setContent(QString::fromUtf8(u_bytes.data(), u_bytes.size()))) {
            file.close();
            return false;
        }
    }

    file.close();

    if(!d->check(document))
        return false;

    // Clear scene if applicable

    if(!append) {
        d->scene->clear();
        d->graph->clear();
    }

    d->node_map.clear();

    // --

    if(!append) {
        d->root = d->scene->root();
        d->node = d->root;
        d->graph->addNode(d->root);
    } else {
        d->node = d->scene->current();
    }

    // Feeding scene with notes
    
    QDomNodeList notes = document.firstChild().childNodes();

    for(int i = 0; i < notes.count(); i++)    
        if(notes.at(i).toElement().tagName() == "note")
            this->readNote(notes.at(i));

    // Feeding scene with nodes

    QDomNodeList nodes = document.firstChild().childNodes();

    for(int i = 0; i < nodes.count(); i++)
        if(nodes.at(i).toElement().tagName() == "node")
            this->readNode(nodes.at(i));

    // Feeding scene with edges

    QDomNodeList edges = document.firstChild().childNodes();

    for(int i = 0; i < edges.count(); i++)
        if(edges.at(i).toElement().tagName() == "edge")
            this->readEdge(edges.at(i));

    // --
    
    if(!append)
        d->scene->setRoot(d->root);

    d->graph->layout();

    // --
    
    return true;
}

dtkComposerSceneNote *dtkComposerReader::readNote(QDomNode node)
{
    qreal x = node.toElement().attribute("x").toFloat();
    qreal y = node.toElement().attribute("y").toFloat();
    qreal w = node.toElement().attribute("w").toFloat();
    qreal h = node.toElement().attribute("h").toFloat();
    
    dtkComposerSceneNote *note = new dtkComposerSceneNote;
    note->setPos(QPointF(x, y));
    note->setSize(QSizeF(w, h));
    note->setText(node.childNodes().at(0).toText().data());
    
    d->node->addNote(note);

    note->setParent(d->node);

    return note;
}

dtkComposerSceneNode *dtkComposerReader::readNode(QDomNode node)
{
    QDomNodeList childNodes = node.childNodes();

    QList<QDomNode> ports;
    QList<QDomNode> notes;
    QList<QDomNode> nodes;
    QList<QDomNode> edges;
    QList<QDomNode> blocks;

    for(int i = 0; i < childNodes.count(); i++)
        if(childNodes.at(i).toElement().tagName() == "port")
            ports << childNodes.at(i);

    for(int i = 0; i < childNodes.count(); i++)
        if(childNodes.at(i).toElement().tagName() == "note")
            notes << childNodes.at(i);

    for(int i = 0; i < childNodes.count(); i++)
        if(childNodes.at(i).toElement().tagName() == "node")
            nodes << childNodes.at(i);

    for(int i = 0; i < childNodes.count(); i++)
        if(childNodes.at(i).toElement().tagName() == "edge")
            edges << childNodes.at(i);

    for(int i = 0; i < childNodes.count(); i++)
        if(childNodes.at(i).toElement().tagName() == "block")
            blocks << childNodes.at(i);

    // --

    dtkComposerSceneNode *n = NULL;

    if(blocks.count()) {

        qreal w = node.toElement().attribute("w").toFloat();
        qreal h = node.toElement().attribute("h").toFloat();

        n = new dtkComposerSceneNodeControl;
        n->wrap(d->factory->create(node.toElement().attribute("type")));
        n->setParent(d->node);
        d->node->addNode(n);
        d->graph->addNode(n);
        n->resize(w, h);

    } else if(node.toElement().tagName() == "block") {

        n = d->control->blocks().at(node.toElement().attribute("blockid").toInt());

    } else if(notes.count() || nodes.count() || edges.count()) {

        n = new dtkComposerSceneNodeComposite;
        n->wrap(new dtkComposerNodeComposite);
        n->setParent(d->node);
        d->node->addNode(n);
        d->graph->addNode(n);

    } else {

        n = new dtkComposerSceneNodeLeaf;
        n->wrap(d->factory->create(node.toElement().attribute("type")));
        n->setParent(d->node);
        d->node->addNode(n);
        d->graph->addNode(n);

    }

    QPointF position;
    
    if(node.toElement().hasAttribute("x"))
        position.setX(node.toElement().attribute("x").toFloat());
    
    if(node.toElement().hasAttribute("y"))
        position.setY(node.toElement().attribute("y").toFloat());

    n->setPos(position);

    if(node.toElement().hasAttribute("title"))
        n->setTitle(node.toElement().attribute("title"));

    int id = node.toElement().attribute("id").toInt();

    d->node_map.insert(id, n);

    // --

    dtkComposerSceneNodeComposite *t = d->node;

    if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(n)) {

        control->layout();

        for(int i = 0; i < blocks.count(); i++) {
            d->control = control;
            this->readNode(blocks.at(i));
        }
    }

    if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(n)) {

        d->node = composite;

        for(int i = 0; i < ports.count(); i++) {
            if(ports.at(i).toElement().attribute("type") == "input") {
                dtkComposerScenePort *port = new dtkComposerScenePort(dtkComposerScenePort::Input, composite);
                if (ports.at(i).toElement().hasAttribute("label"))
                    port->setLabel(ports.at(i).toElement().attribute("label"));
                composite->addInputPort(port);
                if (ports.at(i).toElement().attribute("kind") == "proxy") {
                    dtkComposerTransmitter *proxy = new dtkComposerTransmitterProxy(composite->wrapee());
                    composite->wrapee()->appendReceiver(proxy);
                }
                if (ports.at(i).toElement().attribute("kind") == "variant") {
                    dtkComposerTransmitter *variant = new dtkComposerTransmitterVariant(composite->wrapee());
                    composite->wrapee()->appendReceiver(variant);
                }
                if (ports.at(i).toElement().hasAttribute("loop"))
                    port->setLoop(ports.at(i).toElement().attribute("loop").toInt());
            } else {
                dtkComposerScenePort *port = new dtkComposerScenePort(dtkComposerScenePort::Output, composite);
                if (ports.at(i).toElement().hasAttribute("label"))
                    port->setLabel(ports.at(i).toElement().attribute("label"));
                composite->addOutputPort(port);
                if (ports.at(i).toElement().attribute("kind") == "proxy") {
                    dtkComposerTransmitter *proxy = new dtkComposerTransmitterProxy(composite->wrapee());
                    composite->wrapee()->appendEmitter(proxy);
                }
                if (ports.at(i).toElement().attribute("kind") == "variant") {
                    dtkComposerTransmitter *variant = new dtkComposerTransmitterVariant(composite->wrapee());
                    composite->wrapee()->appendEmitter(variant);
                }
                if (ports.at(i).toElement().hasAttribute("loop"))
                    port->setLoop(ports.at(i).toElement().attribute("loop").toInt());
            }
        }

        composite->layout();

        for(int i = 0; i < notes.count(); i++)
            this->readNote(notes.at(i));
        
        for(int i = 0; i < nodes.count(); i++)
            this->readNode(nodes.at(i));
        
        for(int i = 0; i < edges.count(); i++)
            this->readEdge(edges.at(i));
    }

    if(dtkComposerSceneNodeLeaf *leaf = dynamic_cast<dtkComposerSceneNodeLeaf *>(n)) {

        for(int i = 0; i < ports.count(); i++)
            if (ports.at(i).toElement().hasAttribute("label"))
                if(ports.at(i).toElement().attribute("type") == "input")
                    leaf->inputPorts().at(ports.at(i).toElement().attribute("id").toUInt())->setLabel(ports.at(i).toElement().attribute("label"));
                else
                    leaf->outputPorts().at(ports.at(i).toElement().attribute("id").toUInt())->setLabel(ports.at(i).toElement().attribute("label"));


        if(dtkComposerNodeInteger *integer = dynamic_cast<dtkComposerNodeInteger *>(leaf->wrapee())) {

            for(int i = 0; i < childNodes.count(); i++) {
                if(childNodes.at(i).toElement().tagName() == "value") {
                    integer->setValue(childNodes.at(i).childNodes().at(0).toText().data().toLongLong());
                }       
            }
        }

        if(dtkComposerNodeReal *real = dynamic_cast<dtkComposerNodeReal *>(leaf->wrapee())) {

            for(int i = 0; i < childNodes.count(); i++) {
                if(childNodes.at(i).toElement().tagName() == "value") {
                    real->setValue(childNodes.at(i).childNodes().at(0).toText().data().toDouble());
                }       
            }
        }        
    }

    d->node = t;

    // --

    return n;
}

dtkComposerSceneEdge *dtkComposerReader::readEdge(QDomNode node)
{
    QDomElement source = node.firstChildElement("source");
    QDomElement destin = node.firstChildElement("destination");
    
    int source_node = source.attribute("node").toInt();
    int destin_node = destin.attribute("node").toInt();
    
    int source_id = source.attribute("id").toInt();
    int destin_id = destin.attribute("id").toInt();

    QString source_type = source.attribute("type");
    QString destin_type = destin.attribute("type");
    
    dtkComposerSceneEdge *edge = new dtkComposerSceneEdge;
    if(source_type == "input")
        edge->setSource(d->node_map.value(source_node)->inputPorts().at(source_id));
    else
        edge->setSource(d->node_map.value(source_node)->outputPorts().at(source_id));
    if(destin_type == "input")
        edge->setDestination(d->node_map.value(destin_node)->inputPorts().at(destin_id));
    else
        edge->setDestination(d->node_map.value(destin_node)->outputPorts().at(destin_id));
    edge->link();
    edge->adjust();
    
    d->node->addEdge(edge);

    edge->setParent(d->node);

    dtkComposerTransmitterConnection(d->scene->root(), d->node, edge);

    d->graph->addEdge(edge);

    return edge;
}
