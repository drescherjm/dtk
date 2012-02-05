/* dtkComposerReader.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:41:08 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb  5 16:19:23 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 206
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerFactory.h"
#include "dtkComposerReader.h"
#include "dtkComposerScene.h"
#include "dtkComposerScene_p.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerSceneNote.h"
#include "dtkComposerScenePort.h"

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

public:
    QHash<int, dtkComposerSceneNode *> node_map;

public:
    dtkComposerSceneNodeComposite *root;
    dtkComposerSceneNodeComposite *node;
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

    if(!append)
        d->scene->clear();

    d->node_map.clear();

    // --

    if(!append) {
        d->root = d->scene->root();
        d->node = d->root;
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

    return note;
}

dtkComposerSceneNode *dtkComposerReader::readNode(QDomNode node)
{
    QDomNodeList childNodes = node.childNodes();

    QList<QDomNode> notes;
    QList<QDomNode> nodes;
    QList<QDomNode> edges;

    for(int i = 0; i < childNodes.count(); i++)
        if(childNodes.at(i).toElement().tagName() == "note")
            notes << childNodes.at(i);

    for(int i = 0; i < childNodes.count(); i++)
        if(childNodes.at(i).toElement().tagName() == "node")
            nodes << childNodes.at(i);

    for(int i = 0; i < childNodes.count(); i++)
        if(childNodes.at(i).toElement().tagName() == "edge")
            edges << childNodes.at(i);

    // --

    dtkComposerSceneNode *n = NULL;

    if(notes.count() || nodes.count() || edges.count())
        n = new dtkComposerSceneNodeComposite;
    else
        n = d->factory->create("");

    n->setParent(d->node);

    QPointF position;
    
    if(node.toElement().hasAttribute("x"))
        position.setX(node.toElement().attribute("x").toFloat());
    
    if(node.toElement().hasAttribute("y"))
        position.setY(node.toElement().attribute("y").toFloat());

    n->setPos(position);

    int id = node.toElement().attribute("id").toInt();

    d->node_map.insert(id, n);

    d->node->addNode(n);

    // --

    dtkComposerSceneNodeComposite *t = d->node;

    if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(n)) {

        d->node = composite;

        for(int i = 0; i < notes.count(); i++)
            this->readNote(notes.at(i));
        
        for(int i = 0; i < nodes.count(); i++)
            this->readNode(nodes.at(i));
        
        for(int i = 0; i < edges.count(); i++)
            this->readEdge(edges.at(i));
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
    
    dtkComposerSceneEdge *edge = new dtkComposerSceneEdge;
    edge->setSource(d->node_map.value(source_node)->port(source_id));
    edge->setDestination(d->node_map.value(destin_node)->port(destin_id));
    edge->link();
    edge->adjust();
    
    d->node->addEdge(edge);

    return edge;
}
