/* dtkComposerNodeControl.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:49:38 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Oct 24 15:17:18 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 836
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

    bool block_added;
    bool block_removed;

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
    this->setSize(400, 246);

    d->color = Qt::transparent;

    d->block_added = false;
    d->block_removed = false;
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

    d->block_added = true;

    this->layout();

    return block;
}

int dtkComposerNodeControl::removeBlock(dtkComposerNodeControlBlock *block, bool clean)
{
    int removed_blocks = 0;

    if (d->blocks.contains(block)) {

        removed_blocks = d->blocks.removeAll(block); 
        
        d->block_removed = true;

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
    return QVariant();
}

dtkComposerNodeProperty *dtkComposerNodeControl::inputProperty(void)
{
    return d->property_input;
}

void dtkComposerNodeControl::disableInputProperty(void)
{
    this->removeInputProperty(d->property_input);
    delete d->property_input;
    d->property_input = NULL;
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
        if (i_route->destination() == d->property_input) {
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

bool dtkComposerNodeControl::dirtyBlockEndNodes(void)
{        
    foreach(dtkComposerEdge *o_route, this->outputRelayRoutes())
        if (o_route->destination()->blockedFrom() == this->currentBlock()->title())
            if (o_route->source()->node()->dirty())
                return true;

    return false;
}

void dtkComposerNodeControl::markDirtyDownstreamNodes(void)
{
    foreach(dtkComposerEdge *o_route, this->outputRoutes())
        if (o_route->source()->blockedFrom() == d->current_block->title())
            o_route->destination()->node()->setDirty(true);
}

void dtkComposerNodeControl::cleanInputActiveRoutes(void)
{
    foreach(dtkComposerEdge *active_route, this->inputActiveRoutes()) {
        foreach(dtkComposerEdge *i_route, active_route->destination()->node()->allRoutes()) {
            if (i_route == active_route) {
                active_route->destination()->node()->removeRoute(i_route);
                break;
            }
        }
        this->removeInputActiveRoute(active_route);
        delete active_route;
        active_route = NULL;
    }
}

void dtkComposerNodeControl::cleanOutputActiveRoutes(void)
{            
    foreach(dtkComposerEdge *active_route, this->outputActiveRoutes()) {
        foreach(dtkComposerEdge *i_route, active_route->destination()->node()->allRoutes()) {
            if (i_route == active_route) {
                active_route->destination()->node()->removeRoute(i_route);
                break;
            }
        }
        this->removeOutputActiveRoute(active_route);
        delete active_route;
        active_route = NULL;
    }
}

void dtkComposerNodeControl::pull(dtkComposerEdge *i_route, dtkComposerNodeProperty *property)
{
    foreach(dtkComposerEdge *relay_route, this->inputRelayRoutes()) {
        if (relay_route->source() == property) {
                
            dtkComposerEdge *route = new dtkComposerEdge;
            route->setSource(i_route->source());
            route->setDestination(relay_route->destination());
                
            relay_route->destination()->node()->addInputRoute(route);
            this->addInputActiveRoute(route);
        }
    }
}

void dtkComposerNodeControl::run(void)
{
    foreach(dtkComposerNode *child, this->currentBlock()->nodes())
        child->setDirty(true);

    foreach(dtkComposerNode *child, this->currentBlock()->startNodes())
        child->update();
}

void dtkComposerNodeControl::push(dtkComposerEdge *o_route, dtkComposerNodeProperty *property)
{
    foreach(dtkComposerEdge *relay_route, this->outputRelayRoutes()) {
        if (relay_route->destination() == o_route->source()) {
            
            dtkComposerEdge *route = new dtkComposerEdge;
            route->setSource(relay_route->source());
            route->setDestination(o_route->destination());
            
            this->addOutputActiveRoute(route);
            
            if (o_route->destination()->type() == dtkComposerNodeProperty::HybridOutput || 
                o_route->destination()->type() == dtkComposerNodeProperty::PassThroughOutput || 
                (o_route->destination()->type() == dtkComposerNodeProperty::Input && o_route->destination()->node()->kind() == dtkComposerNode::Control && relay_route->source()->node()->isChildOfControlNode(o_route->destination()->node()))) {
                
                dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(o_route->destination()->node());
                output_control_node->addOutputRelayRoute(route);
                
            } else {
                
                o_route->destination()->node()->addInputRoute(route);
                
            }
        }
    }
}

void dtkComposerNodeControl::layout(void)
{
    dtkComposerNode::layout();

    if (d->property_input)
        d->property_input->setRect(QRectF(this->boundingRect().left() + this->nodeRadius(), 
                                          this->boundingRect().top()  + this->nodeRadius(), 
                                          2 * + this->nodeRadius(), 
                                          2 * + this->nodeRadius()));

    this->resize();
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
    QRectF mini_rect = this->minimalBoundingRect();
    QRectF node_rect = this->boundingRect();

    qreal dw_min =  mini_rect.width() -  node_rect.width();
    qreal dh_min = mini_rect.height() - node_rect.height();

    dw = dw > dw_min ? dw : dw_min;
    dh = dh > dh_min ? dh : dh_min;

    this->setSize(node_rect.width() + dw, node_rect.height() + dh);

    dh /= d->blocks.count();
    foreach(dtkComposerNodeControlBlock *block, d->blocks)
        block->setHeight(block->height() + block->heightRatio() * dh);
}

void dtkComposerNodeControl::resize(void)
{
    if (d->block_added) {

        QRectF node_rect = this->boundingRect();
        QRectF mini_rect = this->minimalBoundingRect();

        if (node_rect.height() < mini_rect.height()) {

            this->setPos(this->pos().x(), this->pos().y() - (mini_rect.height() - node_rect.height()));
            this->setSize(node_rect.width(), mini_rect.height());
            foreach(dtkComposerNodeControlBlock *block, d->blocks)
                block->setHeight((mini_rect.height() - 46) / d->blocks.count());

        } else {

            foreach(dtkComposerNodeControlBlock *block, d->blocks)
                block->setHeight((node_rect.height() - 46) / d->blocks.count());
        }

        d->block_added = false;

    } else if (d->block_removed) {

        QRectF node_rect = this->boundingRect();

        foreach(dtkComposerNodeControlBlock *block, d->blocks)
            block->setHeight((node_rect.height() - 46) / d->blocks.count());

        d->block_removed = false;
    }
}

QRectF dtkComposerNodeControl::minimalBoundingRect(void)
{
    qreal min_height = 200;
    qreal  min_width = 400;
    QRectF node_rect(this->boundingRect().left(), this->boundingRect().top(), min_width, min_height);

    QRectF block_rect;
    foreach(dtkComposerNodeControlBlock *block, d->blocks) {
        block_rect = block->mapRectToParent(block->minimalBoundingRect());
        min_height = min_height > block_rect.height() ? min_height : block_rect.height();
        min_width  =  min_width >  block_rect.width() ?  min_width :  block_rect.width();
    }
    min_height *= d->blocks.count();
    
    node_rect.setWidth(min_width);
    node_rect.setHeight(min_height + 46); // Add header and footer

    return node_rect;
}

void dtkComposerNodeControl::setColor(const QColor& color)
{
    d->color = color;
}

void dtkComposerNodeControl::setInputPropertyName(const QString& name)
{
    d->property_input->setName(name);
}
