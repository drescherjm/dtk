/* dtkComposerNodeControl.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:49:38 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 10 14:32:17 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 998
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeControl_p.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeLoop.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerScene.h"

#include <dtkCore/dtkGlobal>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControl implementation
// /////////////////////////////////////////////////////////////////

//! Constructs a control node.
/*! 
 *  
 */
dtkComposerNodeControl::dtkComposerNodeControl(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeControlPrivate)
{
    d->current_block = NULL;

    d->property_input = new dtkComposerNodeProperty("condition", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);
    this->g->appendLeftProperty(d->property_input);

    this->setAcceptHoverEvents(true);
    this->setKind(dtkComposerNode::Control);
    this->setResizable(true);
    this->setZValue(-2000);
    this->setSize(400, 246);

    d->block_added = false;
    d->block_removed = false;
    d->running = false;

    d->color = Qt::transparent;
}

//! Destroys control node.
/*! 
 *  
 */
dtkComposerNodeControl::~dtkComposerNodeControl(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// Methods dealing with composition graphical logics.
// /////////////////////////////////////////////////////////////////

//! Appends \a block in the list of blocks.
/*! 
 *  Automatic redraw is performed.
 */
void dtkComposerNodeControl::appendBlock(dtkComposerNodeControlBlock *block)
{
    if (d->blocks.contains(block))
        return;

    d->blocks << block;
    d->block_added = true;
    this->layout();
}

//! Removes \a block from the list of blocks.
/*! 
 *  Automatic redraw is performed.
 */
void dtkComposerNodeControl::removeBlock(dtkComposerNodeControlBlock *block)
{
    block->clear();

    d->blocks.removeAll(block);

    d->block_removed = true;

    delete block;
    block = NULL;

    this->layout();
}

//! Sets \a block as the current block.
/*! 
 *  The current block is typically the place where the logic of the
 *  control node is performed. The current block can vary dynamically
 *  according to the conditions arising in the composer logic.
 */
void dtkComposerNodeControl::setCurrentBlock(dtkComposerNodeControlBlock *block)
{
    d->current_block = block;
}

//! Appends a property defined by its \a name, its \a behavior and its
//! \a multiplicity in the list of left and right properties of \a
//! block.
/*! 
 *  When block already contains a left or a right property with the
 *  same name, nothing is done.
 */
void dtkComposerNodeControl::appendBlockProperty(const QString& name, dtkComposerNodeProperty::Behavior behavior, dtkComposerNodeProperty::Multiplicity multiplicity, dtkComposerNodeControlBlock *block)
{
    if (block->property(name, dtkComposerNodeProperty::Left) || 
        block->property(name, dtkComposerNodeProperty::Right)) {
        qDebug() << QString("Property %1 already exists. Please choose another name.").arg(name);
        return;
    }

    dtkComposerNodeProperty *left_property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::Left, behavior, multiplicity, this);
    left_property->setType(dtkComposerNodeProperty::Generic);
    left_property->setBlockedFrom(block->title());

    block->appendLeftProperty(left_property);
    this->g->appendLeftProperty(left_property);

    dtkComposerNodeProperty *right_property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::Right, behavior, multiplicity, this);
    right_property->setType(dtkComposerNodeProperty::Generic);
    right_property->setBlockedFrom(block->title());

    block->appendRightProperty(right_property);
    this->g->appendRightProperty(right_property);
}

//! Appends a property defined by its \a name, its \a behavior and its
//! \a multiplicity in the list of left properties of \a block.
/*! 
 *  When block already contains a left property with the same name,
 *  nothing is done.
 */
void dtkComposerNodeControl::appendBlockLeftProperty(const QString& name, dtkComposerNodeProperty::Behavior behavior, dtkComposerNodeProperty::Multiplicity multiplicity, dtkComposerNodeControlBlock *block)
{
    if (block->property(name, dtkComposerNodeProperty::Left)) {
        qDebug() << QString("Property %1 already exists. Please choose another name.").arg(name);
        return;
    }

    dtkComposerNodeProperty *property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::Left, behavior, multiplicity, this);
    property->setType(dtkComposerNodeProperty::Generic);
    property->setBlockedFrom(block->title());

    block->appendLeftProperty(property);
    this->g->appendLeftProperty(property);
}

//! Appends a property defined by its \a name, its \a behavior and its
//! \a multiplicity in the list of right properties of \a block.
/*! 
 *  When block already contains a right property with the same name,
 *  nothing is done.
 */
void dtkComposerNodeControl::appendBlockRightProperty(const QString& name, dtkComposerNodeProperty::Behavior behavior, dtkComposerNodeProperty::Multiplicity multiplicity, dtkComposerNodeControlBlock *block)
{
    if (block->property(name, dtkComposerNodeProperty::Right)) {
        qDebug() << QString("Property %1 already exists. Please choose another name.").arg(name);
        return;
    }

    dtkComposerNodeProperty *property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::Right, behavior, multiplicity, this);
    property->setType(dtkComposerNodeProperty::Generic);
    property->setBlockedFrom(block->title());

    block->appendRightProperty(property);
    this->g->appendRightProperty(property);
}

//! Removes a property defined by its \a name from the list of left
//! and right properties of \a block.
/*! 
 *  When block does not contain this property, nothing is done.
 */
void dtkComposerNodeControl::removeBlockProperty(const QString& name, dtkComposerNodeProperty::Behavior behavior, dtkComposerNodeControlBlock *block)
{
    if (!block->property(name, dtkComposerNodeProperty::Left) &&
        !block->property(name, dtkComposerNodeProperty::Right)) {
        qDebug() << QString("No property named %1 exists. Nothing is done.").arg(name);
        return;
    }

    if (dtkComposerScene *scene = dynamic_cast<dtkComposerScene *>(this->scene())) {

        dtkComposerNodeProperty *property = block->property(name, dtkComposerNodeProperty::Left);

        if (property) {

            if (property->behavior() == behavior) {

                block->removeLeftProperty(property);
       
                foreach(dtkComposerEdge *edge, this->g->leftEdges()) {
                    if(edge->destination() == property)
                        scene->removeEdge(edge);
                }
                
                foreach(dtkComposerEdge *edge, this->g->leftRelayEdges()) {
                    if(edge->source() == property)
                        scene->removeEdge(edge);
                }
                
                this->g->removeLeftProperty(property);
                delete property;

            } else {

                qDebug() << DTK_PRETTY_FUNCTION << "The input behavior does not match with the left property of name" << name;

            }
                
        } else {

                qDebug() << DTK_PRETTY_FUNCTION << "Left property of name" << name << "does not exist.";

        }

        property = block->property(name, dtkComposerNodeProperty::Right);

        if (property) {

            if (property->behavior() == behavior) {

                block->removeRightProperty(property);
       
                foreach(dtkComposerEdge *edge, this->g->rightEdges()) {
                    if(edge->source() == property)
                        scene->removeEdge(edge);
                }
            
                foreach(dtkComposerEdge *edge, this->g->rightRelayEdges()) {
                    if(edge->destination() == property)
                        scene->removeEdge(edge);
                }
                    
                this->g->removeRightProperty(property);
                delete property;

            } else {

                qDebug() << DTK_PRETTY_FUNCTION << "The input behavior does not match with the right property of name" << name;

            }
                
        } else {

                qDebug() << DTK_PRETTY_FUNCTION << "Right property of name" << name << "does not exist.";

        }
    }
}

//! Removes a property defined by its \a name from the list of right
//! properties of \a block.
/*! 
 *  When block does not contain this property, nothing is done.
 */
void dtkComposerNodeControl::removeBlockLeftProperty(const QString& name, dtkComposerNodeProperty::Behavior behavior, dtkComposerNodeControlBlock *block)
{
    if (!block->property(name, dtkComposerNodeProperty::Left)) {
        qDebug() << QString("No left property named %1 exists. Nothing is done.").arg(name);
        return;
    }

    if (dtkComposerScene *scene = dynamic_cast<dtkComposerScene *>(this->scene())) {

        dtkComposerNodeProperty *property = block->property(name, dtkComposerNodeProperty::Left);

        if (property->behavior() == behavior) {

            block->removeLeftProperty(property);
            
            foreach(dtkComposerEdge *edge, this->g->leftEdges()) {
                if(edge->destination() == property)
                    scene->removeEdge(edge);
            }
            
            foreach(dtkComposerEdge *edge, this->g->leftRelayEdges()) {
                if(edge->source() == property)
                    scene->removeEdge(edge);
            }
            
            this->g->removeLeftProperty(property);
            delete property;
            
        } else {
            
            qDebug() << DTK_PRETTY_FUNCTION << "The input behavior does not match with the left property of name" << name;
            
        }
    }
}

//! Removes a property defined by its \a name from the list of left
//! properties of \a block.
/*! 
 *  When block does not contain this property, nothing is done.
 */
void dtkComposerNodeControl::removeBlockRightProperty(const QString& name, dtkComposerNodeProperty::Behavior behavior, dtkComposerNodeControlBlock *block)
{    
    if (!block->property(name, dtkComposerNodeProperty::Right)) {
        qDebug() << QString("No right property named %1 exists. Nothing is done.").arg(name);
        return;
    }

    if (dtkComposerScene *scene = dynamic_cast<dtkComposerScene *>(this->scene())) {

        dtkComposerNodeProperty *property = block->property(name, dtkComposerNodeProperty::Right);

        if (property->behavior() == behavior) {
            
            block->removeRightProperty(property);
            
            foreach(dtkComposerEdge *edge, this->g->rightEdges()) {
                if(edge->source() == property)
                    scene->removeEdge(edge);
            }
            
            foreach(dtkComposerEdge *edge, this->g->rightRelayEdges()) {
                if(edge->destination() == property)
                    scene->removeEdge(edge);
            }
            
            this->g->removeRightProperty(property);
            delete property;
            
        } else {
            
            qDebug() << DTK_PRETTY_FUNCTION << "The input behavior does not match with found property";

        }
    }
}

//! Returns list of all the blocks.
/*! 
 *  The current block is typically the place where the logic of the
 *  control node is performed. The current block can vary dynamically
 *  according to the conditions arising in the composer logic.
 *
 *  See also setCurrentBlock.
 */
const QList<dtkComposerNodeControlBlock *>& dtkComposerNodeControl::blocks(void) const
{
    return d->blocks;
}

//! Returns block naming \a title.
/*! 
 *  
 */
dtkComposerNodeControlBlock *dtkComposerNodeControl::block(const QString& title) const
{
    foreach(dtkComposerNodeControlBlock *block, d->blocks)
        if(block->title() == title)
            return block;

    return NULL;
}

//! Returns the current block.
/*! 
 *  
 */
dtkComposerNodeControlBlock *dtkComposerNodeControl::currentBlock(void) const
{
    return d->current_block;
}

//! Returns the list of left properties owned by the block of name \a
//! title.
/*! 
 *  
 */
const QList<dtkComposerNodeProperty *>& dtkComposerNodeControl::leftProperties(const QString& block_title) const
{
    foreach(dtkComposerNodeControlBlock *block, d->blocks)
        if(block->title() == block_title)
            return block->leftProperties();
}

//! Returns the list of right properties owned by the block of name \a
//! title.
/*! 
 *  
 */
const QList<dtkComposerNodeProperty *>& dtkComposerNodeControl::rightProperties(const QString& block_title) const
{
    foreach(dtkComposerNodeControlBlock *block, d->blocks)
        if(block->title() == block_title)
            return block->rightProperties();
}

//! Returns the left property defined by its \a name and owned by the
//! block named \a title.
/*! 
 *  
 */
dtkComposerNodeProperty *dtkComposerNodeControl::leftProperty(const QString& block_title, const QString& name) const
{
    foreach(dtkComposerNodeControlBlock *block, d->blocks)
        if(block->title() == block_title)
            foreach(dtkComposerNodeProperty *property, block->leftProperties())
                if(property->name() == name)
                    return property;

    return NULL;
}

//! Returns the right property defined by its \a name and owned by the
//! block named \a title.
/*! 
 *  
 */
dtkComposerNodeProperty *dtkComposerNodeControl::rightProperty(const QString& block_title, const QString& name) const
{
    foreach(dtkComposerNodeControlBlock *block, d->blocks)
        if(block->title() == block_title)
            foreach(dtkComposerNodeProperty *property, block->rightProperties())
                if(property->name() == name)
                    return property;

    return NULL;
}

// /////////////////////////////////////////////////////////////////
// Methods dealing with composition evaluation logics
// /////////////////////////////////////////////////////////////////

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

QList<dtkComposerEdge *> dtkComposerNodeControl::inputRelayRoutes(void)
{
    return d->input_relay_routes;
}

QList<dtkComposerEdge *> dtkComposerNodeControl::outputRelayRoutes(void)
{
    return d->output_relay_routes;
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

    foreach(dtkComposerEdge *i_route, this->l->leftRoutes()) {
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

    foreach(dtkComposerEdge *i_route, this->l->leftRoutes())
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
    this->g->removeLeftProperty(d->property_input);
    delete d->property_input;
    d->property_input = NULL;
}

void dtkComposerNodeControl::setRunning(bool running)
{
    d->running = running;
}

bool dtkComposerNodeControl::dirtyInputValue(void)
{
    foreach(dtkComposerEdge *i_route, this->l->leftRoutes()) {
        if (i_route->destination() == d->property_input) {
            if(dtkComposerNodeLoop *loop = dynamic_cast<dtkComposerNodeLoop *>(i_route->source()->node())) {

                if(this->isChildOf(loop)) {

                    continue;
                    
                    // if(loop->isRunning()) {
                    //     continue;
                    // } else {
                    //     return true;
                    // }
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
    foreach(dtkComposerEdge *i_route, this->l->leftRoutes()) {
        if (i_route->destination()->blockedFrom() == d->current_block->title()) {
            
            if(dtkComposerNodeLoop *loop = dynamic_cast<dtkComposerNodeLoop *>(i_route->source()->node())) {
                
                if(this->isChildOf(loop)) {

                    continue;

                    // if(loop->isRunning()) {
                    //     continue;
                    // } else {
                    //     return true;
                    // }
                } else {
                    if (i_route->source()->node()->dirty()) {
                        return true;
                    }
                }
                
            } else {
                
                if (i_route->source()->node()->dirty()) {
                    return true;
                }
                
            }
        }
    }

    return false;
}

void dtkComposerNodeControl::markDirtyDownstreamNodes(void)
{
    foreach(dtkComposerEdge *o_route, this->l->rightRoutes())
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
                
            relay_route->destination()->node()->l->appendLeftRoute(route);

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
            
            if (o_route->destination()->type() == dtkComposerNodeProperty::Generic) {
                        
                if (o_route->destination()->position() == dtkComposerNodeProperty::Right) {
                    dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(o_route->destination()->node());
                    output_control_node->addOutputRelayRoute(route);

                } else {
                    o_route->destination()->node()->l->appendLeftRoute(route);                            
                }

            } else if (o_route->destination()->type() == dtkComposerNodeProperty::HybridOutput || 
                o_route->destination()->type() == dtkComposerNodeProperty::PassThroughOutput || 
               (o_route->destination()->type() == dtkComposerNodeProperty::Input && o_route->destination()->node()->kind() == dtkComposerNode::Control && relay_route->source()->node()->isChildOfControlNode(o_route->destination()->node()))) {
                
                dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(o_route->destination()->node());
                output_control_node->addOutputRelayRoute(route);
                
            } else {                
                o_route->destination()->node()->l->appendLeftRoute(route);
            }
        }
    }
}

// /////////////////////////////////////////////////////////////////
// Methods dealing with graphical identity of the control node
// /////////////////////////////////////////////////////////////////

//! Defines the layout of the control node.
/*! 
 *  Reimplemented from dtkComposerNode.
 */
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

//! Defines the control node identity.
/*! 
 *  Reimplemented from QGraphicsItem.
 */
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
    this->prepareGeometryChange();

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
    this->prepareGeometryChange();

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
