/* dtkComposerWriter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:02:49 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Dec  3 00:06:39 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 179
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
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeProcess.h"
#include "dtkComposerScene.h"
#include "dtkComposerWriter.h"

#include <QtXml>

// /////////////////////////////////////////////////////////////////
// dtkComposerWriterPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerWriterPrivate
{
public:
    void writeNode(dtkComposerNode *node, QDomElement& element, QDomDocument& document);

public:
    dtkComposerScene *scene;

    QHash<int, dtkComposerNode *> node_ids;

    int id;
};

void dtkComposerWriterPrivate::writeNode(dtkComposerNode *node, QDomElement& element, QDomDocument& document)
{
    int current_id = id++;

    QDomElement tag = document.createElement("node");
    tag.setAttribute("type", node->type());
    tag.setAttribute("x", QString::number(node->pos().x()));
    tag.setAttribute("y", QString::number(node->pos().y()));
    tag.setAttribute("id", QString::number(current_id));
        
    // -- File node
    
    if(dtkComposerNodeFile *file_node = dynamic_cast<dtkComposerNodeFile *>(node)) {
        
        QString file_name = file_node->value(file_node->outputProperty("name")).toString();
        
        if(!file_name.isEmpty()) {
            
            QDomText text = document.createTextNode(file_name);
            
            QDomElement name = document.createElement("name");
            name.appendChild(text);
            
            tag.appendChild(name);
        }
    }
    
    // -- Process node
    
    if(dtkComposerNodeProcess *process_node = dynamic_cast<dtkComposerNodeProcess *>(node)) {
        
        QString implementation = process_node->implementation();
        
        if(!implementation.isEmpty()) {
            
            QDomText text = document.createTextNode(implementation);
            
            QDomElement implementation = document.createElement("implementation");
            implementation.appendChild(text);
            
            tag.appendChild(implementation);
        }
    }
    
    // -- Composite node
    
    if(node->kind() == dtkComposerNode::Composite) {
        foreach(dtkComposerNode *child, node->childNodes())
            this->writeNode(child, tag, document);
    }
    
    { // -- Generic node
        
        { // -- title
            
            QString node_title = node->title();
            
            QDomText text = document.createTextNode(node_title);
            
            QDomElement title = document.createElement("title");
            title.appendChild(text);
            
            tag.appendChild(title);
        }

        { // -- properties

            foreach(dtkComposerNodeProperty *property, node->inputProperties()) {
                
                QDomElement property_element = document.createElement("property");
                property_element.setAttribute("name", property->name());
                property_element.setAttribute("type", "input");
                property_element.setAttribute("hidden", property->isDisplayed() ? "false" : "true");
                if(node->kind() == dtkComposerNode::Composite)
                    property_element.setAttribute("id", node_ids.key(property->clonedFrom()));
                tag.appendChild(property_element);
            }

            foreach(dtkComposerNodeProperty *property, node->outputProperties()) {
                
                QDomElement property_element = document.createElement("property");
                property_element.setAttribute("name", property->name());
                property_element.setAttribute("type", "output");
                property_element.setAttribute("hidden", property->isDisplayed() ? "false" : "true");
                if(node->kind() == dtkComposerNode::Composite)
                    property_element.setAttribute("id", node_ids.key(property->clonedFrom()));
                tag.appendChild(property_element);
            }
        }
    }

    // --
    
    element.appendChild(tag);
    
    this->node_ids.insert(current_id, node);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerWriter
// /////////////////////////////////////////////////////////////////

dtkComposerWriter::dtkComposerWriter(dtkComposerScene *scene) : QObject(), d(new dtkComposerWriterPrivate)
{
    d->scene = scene;
}

dtkComposerWriter::~dtkComposerWriter(void)
{
    delete d;

    d = NULL;
}

void dtkComposerWriter::write(const QString& fileName)
{
    d->node_ids.clear();
    d->id = 0;

    // Building dom document

    QDomDocument document("dtk");

    QDomElement root = document.createElement("dtk");
    document.appendChild(root);

    // -- Writing nodes

    foreach(dtkComposerNode *node, d->scene->nodes())
        if(!node->parentNode())
            d->writeNode(node, root, document);

    // -- Writing edges

    foreach(dtkComposerEdge *edge, d->scene->edges()) {

        QDomElement source = document.createElement("source");
        source.setAttribute("node", d->node_ids.key(edge->source()->node()));
        source.setAttribute("property", edge->source()->name());

        QDomElement destin = document.createElement("destination");
        destin.setAttribute("node", d->node_ids.key(edge->destination()->node()));
        destin.setAttribute("property", edge->destination()->name());

        QDomElement tag = document.createElement("edge");
        tag.appendChild(source);
        tag.appendChild(destin);

        root.appendChild(tag);
    }

    // Writing file

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
        return;

    QTextStream out(&file); out << document.toString();

    file.close();
}
