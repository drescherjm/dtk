/* dtkComposerReader.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:02:49 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Dec  3 00:06:31 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 330
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

#include <dtkCore/dtkGlobal.h>

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
    
    dtkComposerNode *n = NULL;

    if(node.toElement().attribute("type") != "dtkComposerNodeComposite")
        n = this->scene->createNode(node.toElement().attribute("type"), position);

    int id = node.toElement().attribute("id").toInt();

    // Composite node

    if(node.toElement().attribute("type") == "dtkComposerNodeComposite") {

        QList<dtkComposerNode *> child_nodes;

        QDomNodeList children = node.childNodes();

        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "node")
                continue;
         
            child_nodes << this->readNode(children.at(i));
        }

        n = this->scene->createGroup(child_nodes);
    }
    
    // File node
    
    if(dtkComposerNodeFile *file_node = dynamic_cast<dtkComposerNodeFile *>(n)) {
        
        QDomNodeList children = node.childNodes();
        
        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "name")
                continue;

            file_node->setFileName(children.at(i).childNodes().at(0).toText().data());
        }        
    }
    
    // Process node
    
    if(dtkComposerNodeProcess *process_node = dynamic_cast<dtkComposerNodeProcess *>(n)) {
        
        QDomNodeList children = node.childNodes();
        
        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "implementation")
                continue;

            process_node->setupImplementation(children.at(i).childNodes().at(0).toText().data());
        }
    }
    
    // Generic node
    
    { // -- title
        
        QDomNodeList children = node.childNodes();
        
        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "title")
                continue;

            n->setTitle(children.at(i).childNodes().at(0).toText().data());
        }
    }

    { // -- properties
        
        QDomNodeList children = node.childNodes();
        
        for(int i = 0; i < children.count(); i++) {

            if(children.at(i).toElement().tagName() != "property")
                continue;

            QString name = children.at(i).toElement().attribute("name");
            QString type = children.at(i).toElement().attribute("type");
            QString hidden = children.at(i).toElement().attribute("hidden");
            
            int p_id = -1;

            if(children.at(i).toElement().hasAttribute("id"))
                p_id = children.at(i).toElement().attribute("id").toInt();

            if(type == "input") {
                foreach(dtkComposerNodeProperty *property, n->inputProperties()) {
                    if(property->name() == name) {
                        if(p_id >= 0 && p_id == node_map.key(property->clonedFrom())) {
                            if(hidden == "false") {
                                property->setDirty(true);
                            }
                        } else {
                            if(hidden == "true") {
                                property->hide();
                            }
                        }
                    }
                }
            }

            if(type == "output") {
                foreach(dtkComposerNodeProperty *property, n->outputProperties()) {
                    if(property->name() == name) {
                        if(p_id >= 0 && p_id == node_map.key(property->clonedFrom())) {
                            if(hidden == "false") {
                                property->setDirty(true);
                            }
                        } else {
                            if(hidden == "true") {
                                property->hide();
                            }
                        }
                    }
                }
            }
        }
    }

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

    QDomNodeList nodes = doc.firstChild().childNodes();

    for(int i = 0; i < nodes.count(); i++)
        if(nodes.at(i).toElement().tagName() == "node")
            d->readNode(nodes.at(i));

    // Feeding scene with edges

    QDomNodeList edges = doc.firstChild().childNodes();

    for(int i = 0; i < edges.count(); i++) {

        if(edges.at(i).toElement().tagName() != "edge")
            continue;

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
