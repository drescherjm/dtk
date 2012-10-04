/* dtkComposerWriter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:42:34 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Sep 26 15:31:26 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 522
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeLeafData.h"
#include "dtkComposerNodeLeafProcess.h"
#include "dtkComposerNodeLeafView.h"
#include "dtkComposerNodeReal.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerScene.h"
#include "dtkComposerScene_p.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerSceneNote.h"
#include "dtkComposerScenePort.h"
#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterProxy.h"
#include "dtkComposerTransmitterVariant.h"
#include "dtkComposerWriter.h"

#include <dtkLog/dtkLog.h>

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
    d->id    = 0;
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

QDomDocument dtkComposerWriter::toXML(dtkComposerSceneNodeComposite *rootNode, bool addSelf)
{
    QDomDocument document("dtk");

    if(!rootNode)
        return document;

    if (d->id > 0) {
        d->node_ids.clear();
        d->id = 0;
    }

    QDomElement root = document.createElement("dtk");
    document.appendChild(root);

    if (addSelf)
        root.appendChild(this->writeNode(rootNode, root, document));
    else {

        foreach(dtkComposerSceneNote *note, rootNode->notes())
            root.appendChild(this->writeNote(note, root, document));

        foreach(dtkComposerSceneNode *node, rootNode->nodes())
            root.appendChild(this->writeNode(node, root, document));

        foreach(dtkComposerSceneEdge *edge, rootNode->edges())
            if (addSelf || (edge->source()->node() != rootNode && edge->destination()->node() != rootNode))
                root.appendChild(this->writeEdge(edge, root, document));
    }

    return document;
}

void dtkComposerWriter::write(const QString& fileName, Type type)
{
    if(!d->scene)
        return;

    writeNode(d->scene->root(), fileName, type);
}

void dtkComposerWriter::writeNode(dtkComposerSceneNodeComposite *node, const QString& fileName, Type type)
{
    if(!d->scene)
        return;

    QDomDocument document = this->toXML(node, false);

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
    Q_UNUSED(element);

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
    Q_UNUSED(element);

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

        QDomElement child = this->writeNode(control->header(), tag, document);
        tag.appendChild(child);

        foreach(dtkComposerSceneNodeComposite *block, control->blocks()) {
            child = this->writeNode(block, tag, document);
            child.setAttribute("blockid", i++);
            child.setAttribute("w", block->boundingRect().width());
            child.setAttribute("h", block->boundingRect().height());
            tag.appendChild(child);
        }

        child = this->writeNode(control->footer(), tag, document);
        tag.appendChild(child);
    }

    if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node)) {

        if(composite->embedded())
            tag.setTagName("block");

        tag.setAttribute("title", node->title());
        tag.setAttribute("type", composite->wrapee()->type());

        dtkComposerScenePort *port = NULL;

        for(int i = 0; i < composite->inputPorts().count(); i++) {
            port = composite->inputPorts().at(i);
            QDomElement property = document.createElement("port");
            property.setAttribute("id", i);
            property.setAttribute("type", "input");
            property.setAttribute("label", port->label());

            if (port->node()->wrapee()->receivers().at(port->node()->inputPorts().indexOf(port))->required())
                continue;

            if (port->loop())
                property.setAttribute("loop", port->loop());
            if (port->node()->wrapee()->receivers().at(port->node()->inputPorts().indexOf(port))->kind() == dtkComposerTransmitter::Proxy)
                property.setAttribute("kind", "proxy");
            if (port->node()->wrapee()->receivers().at(port->node()->inputPorts().indexOf(port))->kind() == dtkComposerTransmitter::Variant)
                property.setAttribute("kind", "variant");
            tag.appendChild(property);
        }

        port = NULL;

        for(int i = 0; i < composite->outputPorts().count(); i++) {
            port = composite->outputPorts().at(i);
            QDomElement property = document.createElement("port");
            property.setAttribute("id", i);
            property.setAttribute("type", "output");
            property.setAttribute("label", port->label());

            if (port->node()->wrapee()->emitters().at(port->node()->outputPorts().indexOf(port))->required())
                continue;

            if (port->loop())
                property.setAttribute("loop", port->loop());
            if (port->node()->wrapee()->emitters().at(port->node()->outputPorts().indexOf(port))->kind() == dtkComposerTransmitter::Proxy)
                property.setAttribute("kind", "proxy");
            if (port->node()->wrapee()->emitters().at(port->node()->outputPorts().indexOf(port))->kind() == dtkComposerTransmitter::Variant)
                property.setAttribute("kind", "variant");

// --- twin ports

            if(dtkComposerTransmitterVariant *variant = dynamic_cast<dtkComposerTransmitterVariant *>(port->node()->wrapee()->emitters().at(port->node()->outputPorts().indexOf(port)))) {

                if (dtkComposerTransmitterVariant *twin = variant->twin()) {

                    QString block = twin->parentNode()->titleHint();

                    if(block != port->node()->title())
                        property.setAttribute("block", block);

                    dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(port->node()->parent());

                    if(control) {

                    foreach(dtkComposerScenePort *p, control->block(block)->inputPorts())
                        if(p->node()->wrapee()->receivers().at(p->node()->inputPorts().indexOf(p)) == twin)
                            property.setAttribute("twin", p->node()->inputPorts().indexOf(p));

                    }
                }
            }

// --

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

        if (dynamic_cast<dtkComposerNodeLeaf *>(leaf->wrapee())->isHeader())
            tag.setTagName("header");

        if (dynamic_cast<dtkComposerNodeLeaf *>(leaf->wrapee())->isFooter())
            tag.setTagName("footer");

        tag.setAttribute("type", leaf->wrapee()->type());

        if(node->wrapee() && node->title() != node->wrapee()->titleHint())
            tag.setAttribute("title", node->title());

        dtkComposerScenePort *port = NULL;

        for(int i = 0; i < leaf->inputPorts().count(); i++) {
            port = leaf->inputPorts().at(i);
            if(port->label() == leaf->wrapee()->inputLabelHint(i))
                continue;
            QDomElement property = document.createElement("port");
            property.setAttribute("id", i);
            property.setAttribute("type", "input");
            property.setAttribute("label", port->label());
            tag.appendChild(property);
        }

        port = NULL;

        for(int i = 0; i < leaf->outputPorts().count(); i++) {
            port = leaf->outputPorts().at(i);
            if(port->label() == leaf->wrapee()->outputLabelHint(i))
                continue;
            QDomElement property = document.createElement("port");
            property.setAttribute("id", i);
            property.setAttribute("type", "output");
            property.setAttribute("label", port->label());
            tag.appendChild(property);
        }

        if (dtkComposerNodeBoolean *boolean = dynamic_cast<dtkComposerNodeBoolean *>(node->wrapee())) {

            QDomText text = document.createTextNode(boolean->value() ? "true" : "false");

            QDomElement value = document.createElement("value");
            value.appendChild(text);

            tag.appendChild(value);
        }

        if (dtkComposerNodeInteger *integer = dynamic_cast<dtkComposerNodeInteger *>(node->wrapee())) {

            QDomText text = document.createTextNode(QString::number(integer->value()));

            QDomElement value = document.createElement("value");
            value.appendChild(text);

            tag.appendChild(value);
        }

        if (dtkComposerNodeReal *real = dynamic_cast<dtkComposerNodeReal *>(node->wrapee())) {

            QDomText text = document.createTextNode(QString::number(real->value()));

            QDomElement value = document.createElement("value");
            value.appendChild(text);

            tag.appendChild(value);
        }

        if (dtkComposerNodeString *s = dynamic_cast<dtkComposerNodeString *>(node->wrapee())) {

            QDomText text = document.createTextNode(s->value());

            QDomElement value = document.createElement("value");
            value.appendChild(text);

            tag.appendChild(value);
        }

        if (dtkComposerNodeFile *f = dynamic_cast<dtkComposerNodeFile *>(node->wrapee())) {

            QDomText text = document.createTextNode(f->value());

            QDomElement value = document.createElement("value");
            value.appendChild(text);

            tag.appendChild(value);
        }
        
        if (dtkComposerNodeLeafData *data_node = dynamic_cast<dtkComposerNodeLeafData *>(node->wrapee())) {

            if (data_node->isAbstractData()) {

                QDomText text = document.createTextNode(data_node->currentImplementation());

                QDomElement implementation = document.createElement("implementation");
                implementation.appendChild(text);

                tag.appendChild(implementation);
            }
        }
        
        if (dtkComposerNodeLeafProcess *process_node = dynamic_cast<dtkComposerNodeLeafProcess *>(node->wrapee())) {

            if (process_node->isAbstractProcess()) {

                QDomText text = document.createTextNode(process_node->currentImplementation());

                QDomElement implementation = document.createElement("implementation");
                implementation.appendChild(text);

                tag.appendChild(implementation);
            }
        }
        
        if (dtkComposerNodeLeafView *view_node = dynamic_cast<dtkComposerNodeLeafView *>(node->wrapee())) {

            if (view_node->isAbstractView()) {

                QDomText text = document.createTextNode(view_node->currentImplementation());

                QDomElement implementation = document.createElement("implementation");
                implementation.appendChild(text);

                tag.appendChild(implementation);
            }
        }

        this->extend(node, tag, document);
    }

    return tag;
}

QDomElement dtkComposerWriter::writeEdge(dtkComposerSceneEdge *edge, QDomElement& element, QDomDocument& document)
{
    Q_UNUSED(element);

    QDomElement source = document.createElement("source");
    source.setAttribute("node", d->node_ids.key(edge->source()->node()));
    if(edge->source()->type() == dtkComposerScenePort::Input) {
        source.setAttribute("id", edge->source()->node()->inputPorts().indexOf(edge->source()));
        source.setAttribute("type", "input");
    } else {
        source.setAttribute("id", edge->source()->node()->outputPorts().indexOf(edge->source()));
        source.setAttribute("type", "output");
    }

    QDomElement destin = document.createElement("destination");
    destin.setAttribute("node", d->node_ids.key(edge->destination()->node()));
    if(edge->destination()->type() == dtkComposerScenePort::Input) {
        destin.setAttribute("id", edge->destination()->node()->inputPorts().indexOf(edge->destination()));
        destin.setAttribute("type", "input");
    } else {
        destin.setAttribute("id", edge->destination()->node()->outputPorts().indexOf(edge->destination()));
        destin.setAttribute("type", "output");
    }

    QDomElement tag = document.createElement("edge");
    tag.appendChild(source);
    tag.appendChild(destin);

    return tag;
}

void dtkComposerWriter::extend(dtkComposerSceneNode *node, QDomElement& element, QDomDocument& document)
{
    Q_UNUSED(node);
    Q_UNUSED(element);
    Q_UNUSED(document);
}
