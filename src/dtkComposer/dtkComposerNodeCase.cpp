/* dtkComposerNodeCase.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:03:58 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Dec 13 13:07:28 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 753
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerEvaluator_p.h"
#include "dtkComposerNodeCase.h"
#include "dtkComposerNodeCase_p.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeLoop.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerRoute.h"
#include "dtkComposerScene.h"

#include <dtkCore/dtkGlobal.h>

// #define DTK_DEBUG_COMPOSER_INTERACTION 1
// #define DTK_DEBUG_COMPOSER_EVALUATION 1

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeCaseButton
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCaseButton : public QGraphicsItem
{
public:
     dtkComposerNodeCaseButton(dtkComposerNodeCase *parent, dtkComposerNodeCasePrivate *parent_d);
    ~dtkComposerNodeCaseButton(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeCase *parent_node;
    dtkComposerNodeCasePrivate *parent_node_d;

    QPainterPath path;
    QString text;
};

dtkComposerNodeCaseButton::dtkComposerNodeCaseButton(dtkComposerNodeCase *parent, dtkComposerNodeCasePrivate *parent_d) : QGraphicsItem(parent)
{
    int margin = 10;
    int length = 30;
    int height = 10;
    int radius =  5;
    int origin_x = -(length + margin) / 2;
    int origin_y = 0.;

    QPainterPath b; b.addRoundedRect(origin_x,              origin_y, margin,          -height,     radius, radius);
    QPainterPath c; c.addRoundedRect(origin_x + margin,     origin_y, length - margin, -height,     radius, radius);
    QPainterPath d; d.addRoundedRect(origin_x + length,     origin_y, margin,          -height,     radius, radius);
    QPainterPath e; e.addRoundedRect(origin_x + margin / 2, origin_y, length,          -height / 2,      0,      0);

    this->path = c.united(e.subtracted(b.united(c.united(d))));

    this->parent_node = parent;
    this->parent_node_d = parent_d;

    this->text = "+";
}

dtkComposerNodeCaseButton::~dtkComposerNodeCaseButton(void)
{    

}

QRectF dtkComposerNodeCaseButton::boundingRect(void) const
{
    return this->path.boundingRect();
}

void dtkComposerNodeCaseButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QLinearGradient gradient(option->rect.left(), option->rect.top(), option->rect.left(), option->rect.bottom());
    gradient.setColorAt(0.0, QColor("#bbbbbb"));
    gradient.setColorAt(0.3, QColor("#333333"));
    gradient.setColorAt(1.0, QColor("#222222"));

    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(gradient);
    painter->drawPath(path);
    
#if defined(Q_WS_MAC)
    QFont font("Lucida Grande", 8);
#else
    QFont font("Lucida Grande", 6);
#endif
    font.setBold(true);

    QFontMetrics metrics(font);
    
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, text);
}

void dtkComposerNodeCaseButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    QString block_name = QString("case%1").arg(this->parent_node->blocks().count()-1);

    this->parent_node_d->createBlock(block_name, this->parent_node);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeCasePrivate implementation
// /////////////////////////////////////////////////////////////////

//! Creates a block defined by its \a title inside the case node \a parent.
/*! 
 *  When block title is default, the block corresponding to default
 *  case is created.
 */
dtkComposerNodeControlBlock *dtkComposerNodeCasePrivate::createBlock(const QString& title, dtkComposerNodeCase *parent)
{
    dtkComposerNodeControlBlock *block = new dtkComposerNodeControlBlock(title, parent);
    parent->appendBlock(block);

    if (title == "default") {

        block->setInteractive(false);

        parent->appendBlockLeftProperty("variable", dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, block);
        parent->appendBlockRightProperty("variable", dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, block);

    } else {

        block->setInteractive(false);
        block->setRemoveButtonVisible(true);

        parent->appendBlockLeftProperty("constant", dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Single, block);
        parent->appendBlockLeftProperty("variable", dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, block);
        parent->appendBlockRightProperty("variable", dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, block);

    }

}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeCase implementation
// /////////////////////////////////////////////////////////////////

//! Constructs a control case node.
/*! 
 *  
 */
dtkComposerNodeCase::dtkComposerNodeCase(dtkComposerNode *parent) : dtkComposerNodeControl(parent), d(new dtkComposerNodeCasePrivate)
{
    d->add_button = new dtkComposerNodeCaseButton(this, d);
    d->add_button->setZValue(this->zValue() + 1);

    d->createBlock("default", this);

    this->setColor(QColor("#922891"));
    this->setInputPropertyName("variable");
    this->setTitle("Case");
    this->setType("dtkComposerCase");
}

//! Destroys control case node.
/*! 
 *  
 */
dtkComposerNodeCase::~dtkComposerNodeCase(void)
{
    delete d;

    d = NULL;
}

//! Creates a block with name \a title.
/*! 
 *  
 */
dtkComposerNodeControlBlock *dtkComposerNodeCase::createBlock(const QString& title)
{
    return d->createBlock(title, this);
}

//! Defines the layout of the control case node.
/*! 
 *  Reimplemented from dtkComposerNodeControl.
 */
void dtkComposerNodeCase::layout(void)
{
    dtkComposerNodeControl::layout();  

    QRectF  node_rect = this->boundingRect();
    qreal node_radius = this->nodeRadius();

    int j;
    qreal offset = 23;

    foreach(dtkComposerNodeControlBlock *block, this->blocks()) {

        block->setRect(QRectF(node_rect.x(),
                              node_rect.y() + offset,
                              node_rect.width(),
                              block->height()));

        offset += block->rect().height();        

        j = 0;
        foreach(dtkComposerNodeProperty *property, block->leftProperties()) {

            property->setRect(QRectF(block->mapRectToParent(block->rect()).left() + node_radius,
                                     block->mapRectToParent(block->rect()).top()  + node_radius * (4*j + 1),
                                     2 * node_radius,
                                     2 * node_radius ));

            if (property->name() == "variable") {
                property->mirror();
                j++;
            }

            j++;
        }
        if (block->title() == "default")
            j = 0;
        else
            j = 1;
        foreach(dtkComposerNodeProperty *property, block->rightProperties()) {

            property->setRect(QRectF(block->mapRectToParent(block->rect()).right() - node_radius * 3,
                                     block->mapRectToParent(block->rect()).top()   + node_radius * (4*j + 1),
                                     2 * node_radius,
                                     2 * node_radius ));

            if (property->name() == "variable")
                j++;

            j++;
        }
    } 

    d->add_button->setPos(node_rect.left() + 0.5 * node_rect.width(), node_rect.bottom());
}

//! Node delegates its own evaluation to the evaluator according to
//! Visitor Design Pattern.
/*! 
 * 
 */
bool dtkComposerNodeCase::evaluate(dtkComposerEvaluatorPrivate *evaluator)
{
    return evaluator->evaluate(this);
}

//! 
/*! 
 * 
 */
void dtkComposerNodeCase::pull(dtkComposerRoute *i_route, dtkComposerNodeProperty *property)
{
    if (property == this->inputProperty()) {
        
        foreach(dtkComposerRoute *relay_route, this->leftRelayRoutes()) {
            if (relay_route->source()->name() == this->inputProperty()->name()) {

                dtkComposerRoute *route = new dtkComposerRoute;
                route->setSource(i_route->source());
                route->setDestination(relay_route->destination());
                
                relay_route->destination()->node()->l->appendLeftRoute(route);
                this->addLeftActiveRoute(route);                
            }
        }

    } else {

        dtkComposerNodeControl::pull(i_route, property);

    }
}

//! 
/*! 
 * 
 */
void dtkComposerNodeCase::push(dtkComposerRoute *o_route, dtkComposerNodeProperty *property)
{
    // if (property->name() == this->inputProperty()->name()) {  

    //     dtkComposerNodeProperty *source = NULL;
    //     foreach(dtkComposerRoute *i_route, this->l->leftRoutes())
    //         if (i_route->destination() == this->inputProperty())
    //             source = i_route->source();

    //     dtkComposerRoute *route = new dtkComposerRoute;
    //     route->setSource(source);
    //     route->setDestination(o_route->destination());
    //     this->addLeftActiveRoute(route);

    //     if (o_route->destination()->type() == dtkComposerNodeProperty::Generic) {
               
    //         if (o_route->destination()->position() == dtkComposerNodeProperty::Right) {
    //             dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(o_route->destination()->node());
    //             output_control_node->addOutputRelayRoute(route);
                
    //         } else {
    //             o_route->destination()->node()->l->appendLeftRoute(route);                            
    //         }
            
    //     } else if (o_route->destination()->type() == dtkComposerNodeProperty::HybridOutput || 
    //         o_route->destination()->type() == dtkComposerNodeProperty::PassThroughOutput || 
    //         (o_route->destination()->type() == dtkComposerNodeProperty::Input && o_route->destination()->node()->kind() == dtkComposerNode::Control && source->node()->isChildOfControlNode(o_route->destination()->node()))) {

    //         dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(o_route->destination()->node());
    //         output_control_node->addOutputRelayRoute(route);
            
    //     } else {

    //         o_route->destination()->node()->l->appendLeftRoute(route);

    //     }

    // } else {

    //     dtkComposerNodeControl::push(o_route, property);

    // }
}
