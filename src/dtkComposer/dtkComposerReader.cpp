/* dtkComposerReader.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:02:49 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Dec  1 00:34:57 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 133
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeProcess.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerReader.h"
#include "dtkComposerScene.h"

#include <QtXml>

// /////////////////////////////////////////////////////////////////
// dtkComposerReaderPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerReaderPrivate
{
public:
    dtkComposerNode *readNode(QDomNode node);

public:
    dtkComposerScene *scene;

    QHash<int, dtkComposerNode *> node_map;
};

dtkComposerNode *dtkComposerReaderPrivate::readNode(QDomNode node)
{
    QPointF position;
    
    if(node.toElement().hasAttribute("x"))
        position.setX(node.toElement().attribute("x").toFloat());
    
    if(node.toElement().hasAttribute("y"))
        position.setY(node.toElement().attribute("y").toFloat());
    
    dtkComposerNode *n;

    if(node.toElement().attribute("type") != "dtkComposerNodeComposite")
        n = this->scene->createNode(node.toElement().attribute("type"), position);
    else
        n = this->scene->createGroup(QList<dtkComposerNode *>());
    
    // Generic node
    
    { // -- title
        
        QDomNodeList children = node.toElement().elementsByTagName("title");
        
        if(!children.isEmpty())
            n->setTitle(children.at(0).childNodes().at(0).toText().data());
    }
    
    // File node
    
    if(dtkComposerNodeFile *file_node = dynamic_cast<dtkComposerNodeFile *>(n)) {
        
        QDomNodeList children = node.toElement().elementsByTagName("name");
        
        if(!children.isEmpty())
            file_node->setFileName(children.at(0).childNodes().at(0).toText().data());
    }
    
    // Process node
    
    if(dtkComposerNodeProcess *process_node = dynamic_cast<dtkComposerNodeProcess *>(n)) {
        
        QDomNodeList children = node.toElement().elementsByTagName("implementation");
        
        if(!children.isEmpty())
            process_node->setupImplementation(children.at(0).childNodes().at(0).toText().data());
    }
    
    if(node.toElement().attribute("type") == "dtkComposerNodeComposite") {

        QDomNodeList children = node.toElement().elementsByTagName("node");
        
        for(int i = 0; i < children.count(); i++) {
         
            dtkComposerNode *nd = this->readNode(children.at(i));
            
            nd->setParentNode(n);
            nd->hide();

            foreach(dtkComposerNodeProperty *property, nd->inputProperties())
                n->addInputProperty(property->clone(n));

            foreach(dtkComposerNodeProperty *property, nd->outputProperties())
                n->addOutputProperty(property->clone(n));

            n->addChildNode(nd);
        }
    }

    // --
    
    int id = node.toElement().attribute("id").toInt();
    
    node_map.insert(id, n);

    return n;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerReader
// /////////////////////////////////////////////////////////////////

dtkComposerReader::dtkComposerReader(dtkComposerScene *scene) : QObject(), d(new dtkComposerReaderPrivate)
{
    d->scene = scene;
}

dtkComposerReader::~dtkComposerReader(void)
{
    delete d;

    d = NULL;
}

void dtkComposerReader::read(const QString& fileName)
{
    // Setting dom document

    QDomDocument doc("dtk");

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly))
        return;

    if (!doc.setContent(&file)) {
        file.close();
        return;
    }

    file.close();

    // Clear scene

    d->scene->clear();

    d->node_map.clear();

    // Feeding scene with nodes

    QDomNodeList nodes = doc.elementsByTagName("node");

    for(int i = 0; i < nodes.count(); i++)
        if(nodes.at(i).parentNode().toElement().tagName() != "node")
            d->scene->addNode(d->readNode(nodes.at(i)));

    // Feeding scene with edges

    QDomNodeList edges = doc.elementsByTagName("edge");

    for(int i = 0; i < edges.count(); i++) {

        QDomElement source = edges.at(i).firstChildElement("source");
        QDomElement destin = edges.at(i).firstChildElement("destination");

        int source_id = source.attribute("node").toInt();
        int destin_id = destin.attribute("node").toInt();
        
        QString source_property = source.attribute("property");
        QString destin_property = destin.attribute("property");

        dtkComposerEdge *edge = new dtkComposerEdge;
        edge->setSource(d->node_map.value(source_id)->outputProperty(source_property));
        edge->setDestination(d->node_map.value(destin_id)->inputProperty(destin_property));
        edge->link();
        edge->show();

        d->scene->addEdge(edge);
    }
}
