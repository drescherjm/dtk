/* dtkComposerWriter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:42:34 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 16:03:38 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 275
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"
#include "dtkComposerScene.h"
#include "dtkComposerScene_p.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
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
        root.appendChild(this->writeNote(note, root, document));
    
    foreach(dtkComposerSceneNode *node, d->scene->root()->nodes())
        root.appendChild(this->writeNode(node, root, document));
    
    foreach(dtkComposerSceneEdge *edge, d->scene->root()->edges())
        root.appendChild(this->writeEdge(edge, root, document));
    
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
    
    // element.appendChild(tag);

    return tag;
}

QDomElement dtkComposerWriter::writeNode(dtkComposerSceneNode *node, QDomElement& element, QDomDocument& document)
{
    int current_id = d->id++; d->node_ids.insert(current_id, node);

    QDomElement tag = document.createElement("node");
    tag.setAttribute("x", QString::number(node->pos().x()));
    tag.setAttribute("y", QString::number(node->pos().y()));
    tag.setAttribute("id", QString::number(current_id));

    if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node)) {

        tag.setAttribute("type", control->wrapee()->type());

        tag.setAttribute("w", control->boundingRect().size().width());
        tag.setAttribute("h", control->boundingRect().size().height());

        if(node->wrapee() && node->title() != node->wrapee()->titleHint())
            tag.setAttribute("title", node->title());

        int i = 0;

        foreach(dtkComposerSceneNodeComposite *block, control->blocks()) {
            QDomElement child = this->writeNode(block, tag, document);
            child.setAttribute("blockid", i++);
            tag.appendChild(child);
        }
    }

    if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node)) {

        if(composite->embedded())
            tag.setTagName("block");

        tag.setAttribute("title", node->title());

        foreach(dtkComposerScenePort *port, composite->inputPorts()) {

            QDomElement property = document.createElement("port");
            property.setAttribute("id", port->id());
            property.setAttribute("type", "input");
            property.setAttribute("label", port->label());
            tag.appendChild(property);
        }

        foreach(dtkComposerScenePort *port, composite->outputPorts()) {

            QDomElement property = document.createElement("port");
            property.setAttribute("id", port->id());
            property.setAttribute("type", "output");
            property.setAttribute("label", port->label());
            tag.appendChild(property);
        }

        foreach(dtkComposerSceneNote *note, composite->notes())
            tag.appendChild(this->writeNote(note, tag, document));
        
        foreach(dtkComposerSceneNode *child, composite->nodes())
            tag.appendChild(this->writeNode(child, tag, document));
        
        foreach(dtkComposerSceneEdge *edge, composite->edges())
            tag.appendChild(this->writeEdge(edge, tag, document));

    }

    if(dtkComposerSceneNodeLeaf *leaf = dynamic_cast<dtkComposerSceneNodeLeaf *>(node)) {

        tag.setAttribute("type", leaf->wrapee()->type());

        if(node->wrapee() && node->title() != node->wrapee()->titleHint())
            tag.setAttribute("title", node->title());

        foreach(dtkComposerScenePort *port, leaf->inputPorts()) {

            if(port->label() == leaf->wrapee()->inputLabelHint(port->id()))
                continue;

            QDomElement property = document.createElement("port");
            property.setAttribute("id", port->id());
            property.setAttribute("type", "input");
            property.setAttribute("label", port->label());
            tag.appendChild(property);
        }

        foreach(dtkComposerScenePort *port, leaf->outputPorts()) {

            if(port->label() == leaf->wrapee()->outputLabelHint(port->id()))
                continue;

            QDomElement property = document.createElement("port");
            property.setAttribute("id", port->id());
            property.setAttribute("type", "output");
            property.setAttribute("label", port->label());
            tag.appendChild(property);
        }

        this->extend(node, tag, document);

    }

    return tag;
}

QDomElement dtkComposerWriter::writeEdge(dtkComposerSceneEdge *edge, QDomElement& element, QDomDocument& document)
{
    QDomElement source = document.createElement("source");
    source.setAttribute("node", d->node_ids.key(edge->source()->node()));
    source.setAttribute("id", edge->source()->id());
    if(edge->source()->type() == dtkComposerScenePort::Input)
        source.setAttribute("type", "input");
    else
        source.setAttribute("type", "output");
    
    QDomElement destin = document.createElement("destination");
    destin.setAttribute("node", d->node_ids.key(edge->destination()->node()));
    destin.setAttribute("id", edge->destination()->id());
    if(edge->destination()->type() == dtkComposerScenePort::Input)
        destin.setAttribute("type", "input");
    else
        destin.setAttribute("type", "output");
    
    QDomElement tag = document.createElement("edge");
    tag.appendChild(source);
    tag.appendChild(destin);

    // element.appendChild(tag);

    return tag;
}

void dtkComposerWriter::extend(dtkComposerSceneNode *node, QDomElement& element, QDomDocument& document)
{
    Q_UNUSED(node);
    Q_UNUSED(element);
    Q_UNUSED(document);
}
