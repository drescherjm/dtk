/* dtkComposerReader.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:02:49 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Aug 16 22:24:13 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 60
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNode.h"
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

        int id = nodes.at(i).toElement().attribute("id").toInt();

        node_map.insert(id, node);
    }

    qDebug() << node_map.keys();

    // Feeding scene with edges

    QDomNodeList edges = doc.elementsByTagName("edge");

    for(int i = 0; i < edges.count(); i++) {

        qDebug() << "Reading an edge";
        
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
