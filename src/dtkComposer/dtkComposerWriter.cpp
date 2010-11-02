/* dtkComposerWriter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:02:49 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Nov  1 16:38:02 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 82
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
    dtkComposerScene *scene;
};

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
    // Building dom document

    QDomDocument doc("dtk");

    QDomElement root = doc.createElement("dtk");
    doc.appendChild(root);

    // -- Writing nodes

    int id = 0; QHash<int, dtkComposerNode *> nodes;

    foreach(dtkComposerNode *node, d->scene->nodes()) {

        QDomElement tag = doc.createElement("node");
        tag.setAttribute("type", node->type());
        tag.setAttribute("x", QString::number(node->pos().x()));
        tag.setAttribute("y", QString::number(node->pos().y()));
        tag.setAttribute("id", QString::number(id));

        // -- File node

        if(dtkComposerNodeFile *file_node = dynamic_cast<dtkComposerNodeFile *>(node)) {
           
            QString file_name = file_node->value(file_node->outputProperty("name")).toString();

            if(!file_name.isEmpty()) {
                
                QDomText text = doc.createTextNode(file_name);
                
                QDomElement name = doc.createElement("name");
                name.appendChild(text);

                tag.appendChild(name);
            }
        }

        // -- Process node

        if(dtkComposerNodeProcess *process_node = dynamic_cast<dtkComposerNodeProcess *>(node)) {
           
            QString implementation = process_node->implementation();

            if(!implementation.isEmpty()) {
                
                QDomText text = doc.createTextNode(implementation);
                
                QDomElement implementation = doc.createElement("implementation");
                implementation.appendChild(text);

                tag.appendChild(implementation);
            }
        }

        // --

        root.appendChild(tag);

        nodes.insert(id++, node);
    }

    // -- Writing edges

    foreach(dtkComposerEdge *edge, d->scene->edges()) {

        QDomElement source = doc.createElement("source");
        source.setAttribute("node", nodes.key(edge->source()->node()));
        source.setAttribute("property", edge->source()->name());

        QDomElement destin = doc.createElement("destination");
        destin.setAttribute("node", nodes.key(edge->destination()->node()));
        destin.setAttribute("property", edge->destination()->name());

        QDomElement tag = doc.createElement("edge");
        tag.appendChild(source);
        tag.appendChild(destin);

        root.appendChild(tag);
    }

    // Writing file

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
        return;

    QTextStream out(&file); out << doc.toString();

    file.close();
}
