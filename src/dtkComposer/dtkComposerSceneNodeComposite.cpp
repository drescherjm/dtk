/* dtkComposerSceneNodeComposite.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 14:01:41 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 23 12:56:04 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 443
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeComposite.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNote.h"
#include "dtkComposerScenePort.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeComposite
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodeCompositePrivate
{
public:
    dtkComposerSceneNoteList notes;
    dtkComposerSceneNodeList nodes;
    dtkComposerSceneEdgeList edges;

public:
    QPointF offset;
    QPointF pos;
    QRectF rect;

public:
    bool root;

public:
    bool flattened;
    bool entered;
    bool revealed;
    bool obfuscated;
};

dtkComposerSceneNodeComposite::dtkComposerSceneNodeComposite(void) : dtkComposerSceneNode(), d(new dtkComposerSceneNodeCompositePrivate)
{
    d->rect = QRectF(0, 0, 150, 50);

    d->root = false;

    d->flattened = false;
    d->entered = false;
    d->revealed = false;
    d->obfuscated = false;

    this->layout();
    this->setTitle("Composite");
}

dtkComposerSceneNodeComposite::~dtkComposerSceneNodeComposite(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneNodeComposite::wrap(dtkComposerNode *wrapee)
{
    dtkComposerNodeComposite *composite = dynamic_cast<dtkComposerNodeComposite *>(wrapee);

    if(!composite)
        return;

    dtkComposerSceneNode::wrap(wrapee);
}

void dtkComposerSceneNodeComposite::addNote(dtkComposerSceneNote *note)
{
    d->notes << note;
}

void dtkComposerSceneNodeComposite::removeNote(dtkComposerSceneNote *note)
{
    d->notes.removeAll(note);
}

void dtkComposerSceneNodeComposite::addNode(dtkComposerSceneNode *node)
{
    d->nodes << node;
}

void dtkComposerSceneNodeComposite::removeNode(dtkComposerSceneNode *node)
{
    d->nodes.removeAll(node);
}

void dtkComposerSceneNodeComposite::addEdge(dtkComposerSceneEdge *edge)
{
    d->edges << edge;
}

void dtkComposerSceneNodeComposite::removeEdge(dtkComposerSceneEdge *edge)
{
    d->edges.removeAll(edge);
}

dtkComposerSceneNoteList dtkComposerSceneNodeComposite::notes(void)
{
    return d->notes;
}

dtkComposerSceneNodeList dtkComposerSceneNodeComposite::nodes(void)
{
    return d->nodes;
}

dtkComposerSceneEdgeList dtkComposerSceneNodeComposite::edges(void)
{
    return d->edges;
}

bool dtkComposerSceneNodeComposite::entered(void)
{
    return d->entered;
}

bool dtkComposerSceneNodeComposite::flattened(void)
{
    return d->flattened;
}

void dtkComposerSceneNodeComposite::enter(void)
{
    d->entered = true;

    this->reveal();
}

void dtkComposerSceneNodeComposite::leave(void)
{
    d->entered = false;

    this->unreveal();
}

void dtkComposerSceneNodeComposite::flatten(void)
{
    d->flattened = true;

    this->reveal();
}

void dtkComposerSceneNodeComposite::unflatten(void)
{
    d->flattened = false;

    this->unreveal();
}

void dtkComposerSceneNodeComposite::reveal(void)
{
    d->revealed = true;

    if (this->embedded())
        this->obfuscate();

    this->setFlag(QGraphicsItem::ItemIsMovable, false);

    this->layout();
}

void dtkComposerSceneNodeComposite::unreveal(void)
{
    if(!d->flattened && !d->entered)
        d->revealed = false;

    if(!d->flattened)
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
    else
        this->setFlag(QGraphicsItem::ItemIsMovable, false);

    this->layout();
}

bool dtkComposerSceneNodeComposite::root(void)
{
    return d->root;
}

void dtkComposerSceneNodeComposite::setRoot(bool root)
{
    d->root = root;
}

#include <float.h>

void dtkComposerSceneNodeComposite::layout(void)
{
    if (this->embedded() && !d->entered)
        return;
    
// /////////////////////////////////////////////////////////////////
// Rect calculation
// /////////////////////////////////////////////////////////////////

    if(!d->revealed) {

        d->rect = QRectF(0, 0, 150, 50);

        if(!d->pos.isNull())
            this->setPos(d->pos);

        this->setZValue(0);

    } else {

        qreal w_offset = 100;
        qreal h_offset = 100;

        qreal xmin, xmax;
        qreal ymin, ymax;

        this->boundingBox(xmin, xmax, ymin, ymax);

        qreal w = xmax-xmin; w+= w_offset;
        qreal h = ymax-ymin; h+= h_offset;

        w = qMax(w, 150.0);
        h = qMax(h,  50.0);

        d->rect = QRectF(QPointF(0, 0), QSizeF(w, h));

        this->setPos(xmin - w_offset/2, ymin - h_offset/2);

        this->setZValue(-INT_MAX);
    }

    int header = 15;

    int port_margin_top = 10;
    int port_margin_bottom = 10;
    int port_margin_left = 10;
    int port_spacing = 10;
    
// /////////////////////////////////////////////////////////////////
// Port location
// /////////////////////////////////////////////////////////////////

    for(int i = 0; i < this->inputPorts().count(); i++)
        this->inputPorts().at(i)->setPos(QPointF(port_margin_left, i*this->inputPorts().at(i)->boundingRect().height() + i*port_spacing + port_margin_top + header));
    
    for(int i = 0; i < this->outputPorts().count(); i++)
        this->outputPorts().at(i)->setPos(QPointF(d->rect.right() - port_margin_left - this->outputPorts().at(i)->boundingRect().width(), i*this->outputPorts().at(i)->boundingRect().height() + i*port_spacing + port_margin_top + header));

// /////////////////////////////////////////////////////////////////
// Update edges geometry
// /////////////////////////////////////////////////////////////////

    foreach(dtkComposerSceneEdge *edge, this->inputEdges())
        edge->adjust();

    foreach(dtkComposerSceneEdge *edge, d->edges)
        edge->adjust();

    foreach(dtkComposerSceneEdge *edge, this->outputEdges())
        edge->adjust();
    
// /////////////////////////////////////////////////////////////////
// Height calculation
// /////////////////////////////////////////////////////////////////

    if(!d->revealed) {

        if(this->inputPorts().count() || this->outputPorts().count())
            if(this->inputPorts().count() >= this->outputPorts().count())
                d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), this->inputPorts().count() * this->inputPorts().at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (this->inputPorts().count()-1) * port_spacing + header));
            else
                d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), this->outputPorts().count() * this->outputPorts().at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (this->outputPorts().count()-1) * port_spacing + header));        

    }

    this->update();
}

void dtkComposerSceneNodeComposite::resize(qreal width, qreal height)
{
    d->rect = QRectF(d->rect.topLeft(), QSizeF(width, height));
}

void dtkComposerSceneNodeComposite::obfuscate(void)
{
    QRectF rect = this->sceneBoundingRect();

    d->obfuscated = false;

    foreach(dtkComposerSceneNode *node, d->nodes)
        if (!rect.contains(node->sceneBoundingRect()))
            d->obfuscated = true;

    foreach(dtkComposerSceneNote *note, d->notes)
        if (!rect.contains(note->sceneBoundingRect()))
            d->obfuscated = true;

    foreach(dtkComposerSceneEdge *edge, d->edges)
        if (!rect.contains(edge->sceneBoundingRect()))
            d->obfuscated = true;

    if (d->entered)
        d->obfuscated = false;

    foreach(dtkComposerSceneNode *node, d->nodes)
        node->setVisible(!d->obfuscated);

    foreach(dtkComposerSceneNote *note, d->notes)
        note->setVisible(!d->obfuscated);

    foreach(dtkComposerSceneEdge *edge, d->edges)
        edge->setVisible(!d->obfuscated);

    this->update();
}

void dtkComposerSceneNodeComposite::boundingBox(qreal& x_min, qreal& x_max, qreal& y_min, qreal& y_max)
{
    if(!d->nodes.count()) {
        x_min = 0.0;
        x_max = 0.0;
        y_min = 0.0;
        y_max = 0.0;
        return;
    }

    qreal xmin =  FLT_MAX;
    qreal xmax = -FLT_MAX;
    
    qreal ymin =  FLT_MAX;
    qreal ymax = -FLT_MAX;
    
    foreach(dtkComposerSceneNode *node, d->nodes) {
        xmin = qMin(xmin, node->pos().x());
        xmax = qMax(xmax, node->pos().x() + node->boundingRect().width());
        ymin = qMin(ymin, node->pos().y());
        ymax = qMax(ymax, node->pos().y() + node->boundingRect().height());
    }
    
    x_min = xmin;
    x_max = xmax;
    y_min = ymin;
    y_max = ymax;
}

QRectF dtkComposerSceneNodeComposite::boundingRect(void) const
{
    return d->rect.adjusted(-2, -2, 2, 2);
}

void dtkComposerSceneNodeComposite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal radius = this->embedded() ? 0.0 : 5.0;

    if (this->isSelected()) {
        painter->setPen(QPen(Qt::magenta, 2, Qt::SolidLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRoundedRect(d->rect.adjusted(-2, -2, 2, 2), radius, radius);
    }

    if(d->revealed) {
        painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
    } else {
        QLinearGradient gradiant(d->rect.left(), d->rect.top(), d->rect.left(), d->rect.bottom());
        gradiant.setColorAt(0.0, QColor(Qt::darkGray));
        gradiant.setColorAt(0.3, QColor(Qt::darkGray).darker().darker());
        gradiant.setColorAt(1.0, QColor(Qt::darkGray).darker().darker().darker());

        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
        painter->setBrush(gradiant);
    }

    if(this->embedded() && !d->entered) {
        painter->setPen(Qt::NoPen);
        if(d->obfuscated)
            painter->setBrush(QColor(0, 0, 0, 127));
    }

    painter->drawRoundedRect(d->rect, radius, radius);

    // Drawing node's title

    qreal margin = 5.0;

    QFont font = painter->font();
    QFontMetricsF metrics(font);

    QString title_text = metrics.elidedText(this->title(), Qt::ElideMiddle, this->boundingRect().width()-2-4*margin);
    QPointF title_pos;

    if(!this->embedded() && !d->entered)
        title_pos = QPointF(2*margin, 2*margin + metrics.xHeight());
    else
        title_pos = QPointF(d->rect.width()/2.0 - metrics.width(title_text)/2.0, d->rect.height()/2.0 + metrics.xHeight()/2.0);

    if((this->embedded() && !d->entered) || (!this->embedded() && d->revealed))
        painter->setPen(QPen(QColor(Qt::darkGray)));
    else
        painter->setPen(QPen(QColor(Qt::white)));

    painter->drawText(title_pos, title_text);

    if (d->obfuscated) {

        QFont oFont = QFont(font);
        oFont.setPointSizeF(font.pointSizeF()-2);

        QString title = QString("Obfuscated content. (%1 notes, %2 nodes, %3 edges)")
            .arg(d->notes.count())
            .arg(d->nodes.count())
            .arg(d->edges.count());

        title_text = metrics.elidedText(title, Qt::ElideRight, this->boundingRect().width()-2-4*margin);
        title_pos = QPointF(d->rect.width()/2.0 - metrics.width(title_text)/2.0, d->rect.height()/2.0 + metrics.xHeight()/2.0 + metrics.height() * 1.5);

        painter->setPen(QPen(QColor(Qt::darkGray)));
        painter->setFont(oFont);
        painter->drawText(title_pos, title_text);
    }
}
