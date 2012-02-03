/* dtkComposerWriter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:42:34 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  3 17:22:52 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 161
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerScene.h"
#include "dtkComposerScene_p.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerSceneNote.h"
#include "dtkComposerScenePort.h"
#include "dtkComposerWriter.h"

#include <QtCore>

class dtkComposerWriterPrivate
{
public:
    dtkComposerScene *scene;

public:
    QHash<int, dtkComposerSceneNode *> node_ids;

public:
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

    QDomDocument document("dtk");

    QDomElement root = document.createElement("dtk");
    document.appendChild(root);

    foreach(dtkComposerSceneNote *note, d->scene->root()->notes())
        this->writeNote(note, root, document);
    
    foreach(dtkComposerSceneNode *node, d->scene->root()->nodes())
        this->writeNode(node, root, document);
    
    foreach(dtkComposerSceneEdge *edge, d->scene->root()->edges())
        this->writeEdge(edge, root, document);
    
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

QDomElement dtkComposerWriter::writeNote(dtkComposerSceneNote *note, QDomElement& element, QDomDocument& document)
{
    QDomText text = document.createTextNode(note->text());
    
    QDomElement tag = document.createElement("note");
    tag.setAttribute("x", QString::number(note->pos().x()));
    tag.setAttribute("y", QString::number(note->pos().y()));
    tag.setAttribute("w", QString::number(note->boundingRect().width()));
    tag.setAttribute("h", QString::number(note->boundingRect().height()));
    tag.appendChild(text);
    
    element.appendChild(tag);
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

    if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node)) {

        foreach(dtkComposerSceneNote *note, composite->notes())
            this->writeNote(note, tag, document);
        
        foreach(dtkComposerSceneNode *child, composite->nodes())
            this->writeNode(child, tag, document);
        
        foreach(dtkComposerSceneEdge *edge, composite->edges())
            this->writeEdge(edge, tag, document);

    } else {
        this->extend(node, tag, document);
    }

    return tag;
}

QDomElement dtkComposerWriter::writeEdge(dtkComposerSceneEdge *edge, QDomElement& element, QDomDocument& document)
{
    QDomElement source = document.createElement("source");
    source.setAttribute("node", d->node_ids.key(edge->source()->node()));
    source.setAttribute("id", edge->source()->id());
    
    QDomElement destin = document.createElement("destination");
    destin.setAttribute("node", d->node_ids.key(edge->destination()->node()));
    destin.setAttribute("id", edge->destination()->id());
    
    QDomElement tag = document.createElement("edge");
    tag.appendChild(source);
    tag.appendChild(destin);

    element.appendChild(tag);
}

void dtkComposerWriter::extend(dtkComposerSceneNode *node, QDomElement& element, QDomDocument& document)
{
    Q_UNUSED(node);
    Q_UNUSED(element);
    Q_UNUSED(document);
}
