/* dtkComposerNodeControl.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:49:38 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Mar 18 16:17:53 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 425
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlPrivate
{
public:
    QList<dtkComposerNodeControlBlock *> blocks;

public:
    dtkComposerNodeProperty *property_input;

public:
    QColor color;

    bool dirty;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControl
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControl::dtkComposerNodeControl(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeControlPrivate)
{
    d->color = Qt::transparent;

    d->property_input = new dtkComposerNodeProperty("condition", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    d->property_input->setRect(QRectF(this->boundingRect().left() + 5, this->boundingRect().top() + 5, 10, 10));
    d->property_input->setPos(QPointF(d->property_input->pos().x(), this->boundingRect().top()));

    this->addInputProperty(d->property_input);

    this->setAcceptHoverEvents(true);
    this->setKind(dtkComposerNode::Control);
    this->setResizable(true);
    this->setZValue(-2000);
    this->setSize(400, 400);

    d->dirty = false;
}

dtkComposerNodeControl::~dtkComposerNodeControl(void)
{
    delete d;

    d = NULL;
}

dtkComposerNodeControlBlock *dtkComposerNodeControl::block(const QString& title)
{
    foreach(dtkComposerNodeControlBlock *block, d->blocks)
        if(block->title() == title)
            return block;

    return NULL;
}

dtkComposerNodeControlBlock *dtkComposerNodeControl::addBlock(const QString& title)
{
    dtkComposerNodeControlBlock *block = new dtkComposerNodeControlBlock(title, this);
    
    d->blocks << block;

    d->dirty = true;

    this->layout();

    return block;
}

int dtkComposerNodeControl::removeBlock(dtkComposerNodeControlBlock *block, bool clean)
{
    int removed_blocks = 0;

    if (d->blocks.contains(block)) {

        removed_blocks = d->blocks.removeAll(block); 
        
        d->dirty = true;       

        if (clean) {
            delete block;
            this->layout();
        }
    }

    return removed_blocks;
}

int dtkComposerNodeControl::removeBlock(const QString& title)
{
    foreach(dtkComposerNodeControlBlock *block, d->blocks)
        if(block->title() == title)
            return this->removeBlock(block, true);

    return 0;
}

QList<dtkComposerNodeControlBlock *> dtkComposerNodeControl::blocks(void)
{
    return d->blocks;
}

dtkComposerNodeProperty *dtkComposerNodeControl::inputProperty(const QString& block_title, const QString& name) const
{
    foreach(dtkComposerNodeControlBlock *block, d->blocks)
        if(block->title() == block_title)
            foreach(dtkComposerNodeProperty *property, block->inputProperties())
                if(property->name() == name)
                    return property;

    return NULL;
}

dtkComposerNodeProperty *dtkComposerNodeControl::outputProperty(const QString& block_title, const QString& name) const
{
    foreach(dtkComposerNodeControlBlock *block, d->blocks)
        if(block->title() == block_title)
            foreach(dtkComposerNodeProperty *property, block->outputProperties())
                if(property->name() == name)
                    return property;

    return NULL;
}

void dtkComposerNodeControl::layout(void)
{
    dtkComposerNode::layout();

    if (d->dirty)
        this->resize();

    for(int i = 0; i < d->blocks.count(); i++) {

        d->blocks.at(i)->setRect(QRectF(this->boundingRect().x(),
                                        this->boundingRect().y() + 23 + i * ((this->boundingRect().height() - 46) / d->blocks.count()),
                                        this->boundingRect().width(),
                                        (this->boundingRect().height() - 46) / d->blocks.count()));

        for(int j = 0; j < d->blocks.at(i)->inputProperties().count(); j++) {

            d->blocks.at(i)->inputProperties().at(j)->setRect(
                QRectF(
                    d->blocks.at(i)->rect().left() + this->nodeRadius(),
                    d->blocks.at(i)->rect().top() + this->nodeRadius() * (3*j + 1),
                    2 * this->nodeRadius(),
                    2 * this->nodeRadius()
                ));
        }

        for(int j = 0; j < d->blocks.at(i)->outputProperties().count(); j++) {

            d->blocks.at(i)->outputProperties().at(j)->setRect(
                QRectF(
                    d->blocks.at(i)->rect().right() - 3 * this->nodeRadius(),
                    d->blocks.at(i)->rect().top() + this->nodeRadius() * (3*j + 1),
                    2 * this->nodeRadius(),
                    2 * this->nodeRadius()
                ));
        }
    }
}

void dtkComposerNodeControl::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path;
    path.addRoundedRect(this->boundingRect(), this->nodeRadius(), this->nodeRadius());
    
    QPainterPath blocs_path;
    path.addRect(QRectF(this->boundingRect().topLeft() + QPointF(0, 23), this->boundingRect().bottomRight() - QPointF(0, 23)));

    path -= blocs_path;

    QPainterPath header_path;
    header_path.addRect(QRectF(this->boundingRect().topLeft(), QSizeF(this->boundingRect().width(), 23)));
    header_path &= path;

    QPainterPath footer_path;
    footer_path.addRect(QRectF(this->boundingRect().bottomLeft() - QPointF(0, 23), QSizeF(this->boundingRect().width(), 23)));
    footer_path &= path;

    QLinearGradient header_gradient(header_path.boundingRect().topLeft(), header_path.boundingRect().bottomLeft());
    header_gradient.setColorAt(0.0, QColor(Qt::white));
    header_gradient.setColorAt(0.2, d->color);
    header_gradient.setColorAt(1.0, d->color.darker());

    QLinearGradient footer_gradient(footer_path.boundingRect().topLeft(), footer_path.boundingRect().bottomLeft());
    footer_gradient.setColorAt(0.0, d->color.darker());
    footer_gradient.setColorAt(0.6, d->color.darker());
    footer_gradient.setColorAt(1.0, d->color.darker().darker());
    
    painter->setPen(Qt::NoPen);

    painter->setBrush(header_gradient);
    painter->drawPath(header_path);

    painter->setBrush(footer_gradient);
    painter->drawPath(footer_path);

    dtkComposerNode::paint(painter, option, widget);
}

void dtkComposerNodeControl::resize(const QRectF& rect)
{
    qreal dw =  rect.width() -  this->boundingRect().width();
    qreal dh = rect.height() - this->boundingRect().height();

    this->resize(dw, dh);
}

void dtkComposerNodeControl::resize(const QPointF& delta)
{
    this->resize(delta.x(), delta.y());
}

void dtkComposerNodeControl::resize(qreal dw, qreal dh)
{
    qreal dw_min =  this->minimalBoundingRect().width() -  this->boundingRect().width();
    qreal dh_min = this->minimalBoundingRect().height() - this->boundingRect().height();

    dw = dw > dw_min ? dw : dw_min;
    dh = dh > dh_min ? dh : dh_min;

    this->setSize(this->boundingRect().width() + dw, this->boundingRect().height() + dh);

    foreach(dtkComposerNodeControlBlock *block, d->blocks)
        block->adjustChildNodes(dw, dh / d->blocks.count());
}

void dtkComposerNodeControl::resize(void)
{
    if (this->boundingRect().height() < this->minimalBoundingRect().height() && this->boundingRect().width() < this->minimalBoundingRect().width()) {

        this->setPos(this->pos().x(), this->pos().y() - (this->minimalBoundingRect().height() - this->boundingRect().height()));
        this->setSize(this->minimalBoundingRect().width(), this->minimalBoundingRect().height());

    } else if (this->boundingRect().height() < this->minimalBoundingRect().height()) {

        this->setPos(this->pos().x(), this->pos().y() - (this->minimalBoundingRect().height() - this->boundingRect().height()));
        this->setSize(this->boundingRect().width(), this->minimalBoundingRect().height());

    } else if (this->boundingRect().width() < this->minimalBoundingRect().width()) {

        this->setSize(this->minimalBoundingRect().width(), this->boundingRect().height());
    }

    d->dirty = false;
}

QRectF dtkComposerNodeControl::minimalBoundingRect(void)
{
    qreal min_height = 75;
    qreal min_width = 200;

    if (d->blocks.count()) {
        foreach(dtkComposerNodeControlBlock *block, d->blocks) {
            min_height = min_height > block->minimalBoundingRect().height() ? min_height : block->minimalBoundingRect().height();
            min_width  =  min_width >  block->minimalBoundingRect().width() ?  min_width :  block->minimalBoundingRect().width();
        }
        min_height *= d->blocks.count();
    }
    min_height += 23 + 23; // header + footer

    return QRectF(this->boundingRect().top(), this->boundingRect().top(), min_width, min_height);
}

void dtkComposerNodeControl::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    // qDebug() << DTK_PRETTY_FUNCTION;
}

void dtkComposerNodeControl::onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    // qDebug() << DTK_PRETTY_FUNCTION;
}

bool dtkComposerNodeControl::condition(void)
{
    bool value = false;

    if(!d->property_input)
        return value;

    if(!d->property_input->edge())
        return value;

    QVariant p_value = d->property_input->edge()->source()->node()->value(d->property_input->edge()->source());

    if(!p_value.canConvert(QVariant::Bool))
        return value;
    else
        value = p_value.toBool();

    return value;
}

QVariant dtkComposerNodeControl::value(void)
{
    if(!d->property_input->edge()) {
        qDebug() << DTK_PRETTY_FUNCTION << "No input property edge !!!";
        return QVariant();
    }

    return d->property_input->edge()->source()->node()->value(d->property_input->edge()->source());
}

void dtkComposerNodeControl::setColor(const QColor& color)
{
    d->color = color;
}

void dtkComposerNodeControl::setInputPropertyName(const QString& name)
{
    d->property_input->setName(name);
}
