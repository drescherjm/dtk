/* dtkComposerReader.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:41:08 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  3 17:38:04 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 133
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
    
    d->scene->addNote(note);
}

dtkComposerSceneNode *dtkComposerReader::readNode(QDomNode node)
{
    QPointF position;
    
    if(node.toElement().hasAttribute("x"))
        position.setX(node.toElement().attribute("x").toFloat());
    
    if(node.toElement().hasAttribute("y"))
        position.setY(node.toElement().attribute("y").toFloat());

    dtkComposerSceneNode *n = d->factory->create("");
    n->setPos(position);

    int id = node.toElement().attribute("id").toInt();

    d->node_map.insert(id, n);

    d->scene->addNode(n);

// --

    QDomNodeList notes = node.childNodes();

    for(int i = 0; i < notes.count(); i++)    
        if(notes.at(i).toElement().tagName() == "note")
            this->readNote(notes.at(i));

    QDomNodeList nodes = node.childNodes();

    for(int i = 0; i < nodes.count(); i++)
        if(nodes.at(i).toElement().tagName() == "node")
            this->readNode(nodes.at(i));

    QDomNodeList edges = node.childNodes();

    for(int i = 0; i < edges.count(); i++)
        if(edges.at(i).toElement().tagName() == "edge")
            this->readEdge(edges.at(i));

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
    
    d->scene->addEdge(edge);
}
