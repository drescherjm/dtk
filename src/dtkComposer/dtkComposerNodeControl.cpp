/* dtkComposerNodeControl.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:49:38 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr 27 18:17:42 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 501
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
#include "dtkComposerNodeLoop.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlPrivate
{
public:
    dtkComposerNodeControlBlock *current_block;

public:
    QList<dtkComposerNodeControlBlock *> blocks;

public:
    dtkComposerNodeProperty *property_input;

public:
    QList<dtkComposerEdge *>  input_relay_routes;
    QList<dtkComposerEdge *> output_relay_routes;

    QList<dtkComposerEdge *> input_active_routes;
    QList<dtkComposerEdge *> output_active_routes;

public:
    QColor color;

    bool dirty;

    bool running;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControl
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControl::dtkComposerNodeControl(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeControlPrivate)
{

    d->current_block = NULL;

    d->property_input = new dtkComposerNodeProperty("condition", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    this->addInputProperty(d->property_input);

    this->setAcceptHoverEvents(true);
    this->setKind(dtkComposerNode::Control);
    this->setResizable(true);
    this->setZValue(-2000);
    this->setSize(400, 400);

    d->color = Qt::transparent;

    d->dirty = false;
    d->running = false;
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

dtkComposerNodeControlBlock *dtkComposerNodeControl::currentBlock(void)
{
    return d->current_block;
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

void dtkComposerNodeControl::addInputRelayRoute(dtkComposerEdge *route)
{
    if (!d->input_relay_routes.contains(route))
        d->input_relay_routes << route;
}

void dtkComposerNodeControl::addOutputRelayRoute(dtkComposerEdge *route)
{
    if (!d->output_relay_routes.contains(route))
        d->output_relay_routes << route;
}

void dtkComposerNodeControl::removeInputRelayRoute(dtkComposerEdge *route)
{
    d->input_relay_routes.removeAll(route);
}

void dtkComposerNodeControl::removeOutputRelayRoute(dtkComposerEdge *route)
{
    d->output_relay_routes.removeAll(route);
}

void dtkComposerNodeControl::removeAllRelayRoutes(void)
{
    d->input_relay_routes.clear();
    d->output_relay_routes.clear();
}

QList<dtkComposerEdge *> dtkComposerNodeControl::inputRelayRoutes(void)
{
    return d->input_relay_routes;
}

QList<dtkComposerEdge *> dtkComposerNodeControl::outputRelayRoutes(void)
{
    return d->output_relay_routes;
}

void dtkComposerNodeControl::addInputActiveRoute(dtkComposerEdge *route)
{
    if (!d->input_active_routes.contains(route))
        d->input_active_routes << route;
}

void dtkComposerNodeControl::addOutputActiveRoute(dtkComposerEdge *route)
{
    if (!d->output_active_routes.contains(route))
        d->output_active_routes << route;
}

void dtkComposerNodeControl::removeInputActiveRoute(dtkComposerEdge *route)
{
    d->input_active_routes.removeAll(route);
}

void dtkComposerNodeControl::removeOutputActiveRoute(dtkComposerEdge *route)
{
    d->output_active_routes.removeAll(route);
}

void dtkComposerNodeControl::removeAllActiveRoutes(void)
{
    d->input_active_routes.clear();
    d->output_active_routes.clear();
}

QList<dtkComposerEdge *> dtkComposerNodeControl::inputActiveRoutes(void)
{
    return d->input_active_routes;
}

QList<dtkComposerEdge *> dtkComposerNodeControl::outputActiveRoutes(void)
{
    return d->output_active_routes;
}

QList<dtkComposerEdge *> dtkComposerNodeControl::allRoutes(void)
{
    QList<dtkComposerEdge *> routes;
    routes << dtkComposerNode::allRoutes();
    routes << d->input_relay_routes;
    routes << d->output_relay_routes;
    routes << d->input_active_routes;
    routes << d->output_active_routes;

    return routes;
}

void dtkComposerNodeControl::removeRoute(dtkComposerEdge *route)
{
    dtkComposerNode::removeRoute(route);

    d->input_relay_routes.removeAll(route);
    d->output_relay_routes.removeAll(route);

    d->input_active_routes.removeAll(route);
    d->output_active_routes.removeAll(route);
}

bool dtkComposerNodeControl::isRunning(void)
{
    return d->running;
}

bool dtkComposerNodeControl::condition(void)
{
    bool value = false;

    if(!d->property_input)
        return value;

    if(!d->property_input->edge())
        return value;

    foreach(dtkComposerEdge *i_route, this->inputRoutes()) {
        if (i_route->destination() == d->property_input) {

            QVariant p_value = i_route->source()->node()->value(i_route->source());

            if(!p_value.canConvert(QVariant::Bool))
                return value;
            else
                value = p_value.toBool();
            
            break;
        }
    }

    return value;
}

QVariant dtkComposerNodeControl::value(void)
{
    if(!d->property_input->edge()) {
        qDebug() << DTK_PRETTY_FUNCTION << "No input property edge !!!";
        return QVariant();
    }

    foreach(dtkComposerEdge *i_route, this->inputRoutes())
        if (i_route->destination() == d->property_input)
            return i_route->source()->node()->value(i_route->source());
}

dtkComposerNodeProperty * dtkComposerNodeControl::inputProperty(void)
{
    return d->property_input;
}

void dtkComposerNodeControl::setRunning(bool running)
{
    d->running = running;
}

void dtkComposerNodeControl::setCurrentBlock(dtkComposerNodeControlBlock *block)
{
    d->current_block = block;
}

bool dtkComposerNodeControl::dirtyInputValue(void)
{
    foreach(dtkComposerEdge *i_route, this->inputRoutes()) {
        if (i_route->destination() == this->inputProperty()) {
            if(dtkComposerNodeLoop *loop = dynamic_cast<dtkComposerNodeLoop *>(i_route->source()->node())) {

                if(this->isChildOf(loop)) {
                    if(loop->isPreRunning() || loop->isRunning() || loop->isPostRunning()) {
                        continue;
                    } else {
                        return true;
                    }
                } else {
                    if (i_route->source()->node()->dirty())
                        return true;
                }

            } else {

                if (i_route->source()->node()->dirty())
                    return true;

            }
        }
    }

    return false;
}

bool dtkComposerNodeControl::dirtyUpstreamNodes(void)
{
    foreach(dtkComposerEdge *i_route, this->inputRoutes()) {
        if (i_route->destination()->blockedFrom() == d->current_block->title()) {
            
            if(dtkComposerNodeLoop *loop = dynamic_cast<dtkComposerNodeLoop *>(i_route->source()->node())) {
                
                if(this->isChildOf(loop)) {
                    if(loop->isPreRunning() || loop->isRunning() || loop->isPostRunning()) {
                        continue;
                    } else {
                        return true;
                    }
                } else {
                    if (i_route->source()->node()->dirty())
                        return true;
                }
                
            } else {
                
                if (i_route->source()->node()->dirty())
                    return true;;
                
            }
        }
    }

    return false;
}

void dtkComposerNodeControl::markDirtyDownstreamNodes(void)
{
    foreach(dtkComposerEdge *o_route, this->outputRoutes())
        if (o_route->source()->blockedFrom() == d->current_block->title())
            o_route->destination()->node()->setDirty(true);
}

void dtkComposerNodeControl::layout(void)
{
    dtkComposerNode::layout();

    d->property_input->setRect(QRectF(this->boundingRect().left() + this->nodeRadius(), 
                                      this->boundingRect().top()  + this->nodeRadius(), 
                                      2 * + this->nodeRadius(), 
                                      2 * + this->nodeRadius()));

    if (d->dirty)
        this->resize();

    // for(int i = 0; i < d->blocks.count(); i++) {

    //     d->blocks.at(i)->setRect(QRectF(this->boundingRect().x(),
    //                                     this->boundingRect().y() + 23 + i * ((this->boundingRect().height() - 46) / d->blocks.count()),
    //                                     this->boundingRect().width(),
    //                                     (this->boundingRect().height() - 46) / d->blocks.count()));

    //     for(int j = 0; j < d->blocks.at(i)->inputProperties().count(); j++) {

    //         d->blocks.at(i)->inputProperties().at(j)->setRect(
    //             QRectF(
    //                 d->blocks.at(i)->rect().left() + this->nodeRadius(),
    //                 d->blocks.at(i)->rect().top() + this->nodeRadius() * (4*j + 1),
    //                 2 * this->nodeRadius(),
    //                 2 * this->nodeRadius()
    //                 ));
    //     }

    //     for(int j = 0; j < d->blocks.at(i)->outputProperties().count(); j++) {

    //         d->blocks.at(i)->outputProperties().at(j)->setRect(
    //             QRectF(
    //                 d->blocks.at(i)->rect().right() - 3 * this->nodeRadius(),
    //                 d->blocks.at(i)->rect().top() + this->nodeRadius() * (4*j + 1),
    //                 2 * this->nodeRadius(),
    //                 2 * this->nodeRadius()
    //             ));
    //     }
    // }
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

    return QRectF(this->boundingRect().left(), this->boundingRect().top(), min_width, min_height);
}

void dtkComposerNodeControl::setColor(const QColor& color)
{
    d->color = color;
}

void dtkComposerNodeControl::setInputPropertyName(const QString& name)
{
    d->property_input->setName(name);
}
