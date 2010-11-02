/* dtkComposerReader.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:02:49 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Nov  1 16:31:33 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 87
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
#include "dtkComposerReader.h"
#include "dtkComposerScene.h"

#include <QtXml>

class dtkComposerReaderPrivate
{
public:
    dtkComposerScene *scene;
};

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

    // Ds

    QHash<int, dtkComposerNode *> node_map;

    // Feeding scene with nodes

    QDomNodeList nodes = doc.elementsByTagName("node");

    for(int i = 0; i < nodes.count(); i++) {
        
        QPointF position;

        if(nodes.at(i).toElement().hasAttribute("x"))
            position.setX(nodes.at(i).toElement().attribute("x").toFloat());

        if(nodes.at(i).toElement().hasAttribute("y"))
            position.setY(nodes.at(i).toElement().attribute("y").toFloat());

        dtkComposerNode *node = d->scene->createNode(nodes.at(i).toElement().attribute("type"), position);

        // File node

        if(dtkComposerNodeFile *file_node = dynamic_cast<dtkComposerNodeFile *>(node)) {

            QDomNodeList children = nodes.at(i).toElement().elementsByTagName("name");

            if(!children.isEmpty())
                file_node->setFileName(children.at(0).childNodes().at(0).toText().data());
        }

        // Process node

        if(dtkComposerNodeProcess *process_node = dynamic_cast<dtkComposerNodeProcess *>(node)) {
            
            QDomNodeList children = nodes.at(i).toElement().elementsByTagName("implementation");

            if(!children.isEmpty())
                process_node->setupImplementation(children.at(0).childNodes().at(0).toText().data());
        }

        // --

        int id = nodes.at(i).toElement().attribute("id").toInt();

        node_map.insert(id, node);
    }

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
        edge->setSource(node_map.value(source_id)->outputProperty(source_property));
        edge->setDestination(node_map.value(destin_id)->inputProperty(destin_property));
        edge->link();
        edge->show();

        d->scene->addEdge(edge);
    }
}
