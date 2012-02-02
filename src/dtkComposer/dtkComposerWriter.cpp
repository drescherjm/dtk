/* dtkComposerWriter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:42:34 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb  2 11:59:20 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 82
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerScene.h"
#include "dtkComposerScene_p.h"
#include "dtkComposerWriter.h"

#include <QtCore>

class dtkComposerWriterPrivate
{
public:
    dtkComposerScene *scene;

public:
    QHash<int, dtkComposerSceneNode *> node_ids;

    int id;
};

dtkComposerWriter::dtkComposerWriter(void) : d(new dtkComposerWriterPrivate)
{
    d->scene = NULL;
}

dtkComposerWriter::~dtkComposerWriter(void)
{
    delete d;

    d = NULL;
}

void dtkComposerWriter::setScene(dtkComposerScene *scene)
{
    d->scene = scene;
}

void dtkComposerWriter::write(const QString& fileName, Type type)
{
    if(!d->scene)
        return;

    d->node_ids.clear();
    d->id = 0;

    // Building dom document

    QDomDocument document("dtk");

    QDomElement root = document.createElement("dtk");
    document.appendChild(root);

    // -- Writing nodes

    foreach(dtkComposerSceneNode *node, d->scene->nodes())
        this->writeNode(node, root, document);

    // -- Writing edges

    foreach(dtkComposerSceneEdge *edge, d->scene->edges()) {
        
        QDomElement source = document.createElement("source");
        source.setAttribute("node", d->node_ids.key(dynamic_cast<dtkComposerSceneNode *>(edge->source()->parentItem())));
        source.setAttribute("id", edge->source()->id());
        
        QDomElement destin = document.createElement("destination");
        destin.setAttribute("node", d->node_ids.key(dynamic_cast<dtkComposerSceneNode *>(edge->destination()->parentItem())));
        destin.setAttribute("id", edge->destination()->id());

        QDomElement tag = document.createElement("edge");
        tag.appendChild(source);
        tag.appendChild(destin);

        root.appendChild(tag);
    }

    // -- Writing notes

    foreach(dtkComposerSceneNote *note, d->scene->notes()) {

        QDomText text = document.createTextNode(note->text());

        QDomElement tag = document.createElement("note");
        tag.setAttribute("x", QString::number(note->pos().x()));
        tag.setAttribute("y", QString::number(note->pos().y()));
        tag.setAttribute("w", QString::number(note->boundingRect().width()));
        tag.setAttribute("h", QString::number(note->boundingRect().height()));
        tag.appendChild(text);

        root.appendChild(tag);
    }

    // Writing file

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
        return;

    if(type == dtkComposerWriter::Ascii) {
        QTextStream out(&file); out << document.toString();
    } else {
        QDataStream out(&file); out << qCompress(document.toByteArray().toHex());
    }

    file.close();
}

QDomElement dtkComposerWriter::writeNode(dtkComposerSceneNode *node, QDomElement& element, QDomDocument& document)
{
    int current_id = d->id++;

    QDomElement tag = document.createElement("node");
    tag.setAttribute("x", QString::number(node->pos().x()));
    tag.setAttribute("y", QString::number(node->pos().y()));
    tag.setAttribute("id", QString::number(current_id));
     
    element.appendChild(tag);
    
    d->node_ids.insert(current_id, node);

    this->extend(node, tag, document);

    return tag;
}

void dtkComposerWriter::extend(dtkComposerSceneNode *node, QDomElement& element, QDomDocument& document)
{
    Q_UNUSED(node);
    Q_UNUSED(element);
    Q_UNUSED(document);
}
