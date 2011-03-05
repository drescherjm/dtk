/* dtkComposerNodeCase.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:03:58 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Mar  5 23:34:48 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 171
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeCase.h"
#include "dtkComposerNodeCase_p.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

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
;
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
    int origin_y = parent->boundingRect().height() / 2;

    QPainterPath b; b.addRoundedRect(origin_x,              origin_y, margin,          -height,     radius, radius);
    QPainterPath c; c.addRoundedRect(origin_x + margin,     origin_y, length - margin, -height,     radius, radius);
    QPainterPath d; d.addRoundedRect(origin_x + length,     origin_y, margin,          -height,     radius, radius);
    QPainterPath e; e.addRoundedRect(origin_x + margin / 2, origin_y, length,          -height / 2,      0,      0);

    path = c.united(e.subtracted(b.united(c.united(d))));

    parent_node = parent;
    parent_node_d = parent_d;

    text = "+";
}

dtkComposerNodeCaseButton::~dtkComposerNodeCaseButton(void)
{

}

QRectF dtkComposerNodeCaseButton::boundingRect(void) const
{
    return path.boundingRect();
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

    QString block_name = QString("case%1").arg(parent_node_d->block_cases.count());
    
    parent_node->addBlock(block_name);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeCase
// /////////////////////////////////////////////////////////////////

dtkComposerNodeCase::dtkComposerNodeCase(dtkComposerNode *parent) : dtkComposerNodeControl(parent), d(new dtkComposerNodeCasePrivate)
{
    d->button = new dtkComposerNodeCaseButton(this, d);
    d->button->setPos(0, 0);
    d->button->setZValue(this->zValue() + 1);

    d->block_default = this->addBlock("default");

    this->setColor(QColor("#922891"));
    this->setInputPropertyName("variable");
    this->setTitle("Case");
    this->setType("dtkComposerCase");
}

dtkComposerNodeCase::~dtkComposerNodeCase(void)
{
    delete d;

    d = NULL;
}

dtkComposerNodeControlBlock *dtkComposerNodeCase::addBlock(const QString& title)
{
    dtkComposerNodeControlBlock *block = dtkComposerNodeControl::addBlock(title);

    if(title == "default")
        return block;

    dtkComposerNodeProperty *input_constant = block->addInputProperty("constant", this);
    input_constant->setBlockedFrom(title);
    
    dtkComposerNodeProperty *output_constant = block->addOutputProperty("constant", this);
    output_constant->setBlockedFrom(title);

    this->addInputProperty(input_constant);
    this->addOutputProperty(output_constant);
    
    d->block_cases << block;

    return block;
}

void dtkComposerNodeCase::layout(void)
{
    dtkComposerNodeControl::layout();

    d->button->setPos(this->boundingRect().width()/2 - 150/2, this->boundingRect().bottom() - 200);
}

void dtkComposerNodeCase::update(void)
{
    qDebug() << DTK_PRETTY_FUNCTION;

    int matched = -1;

    QVariant value = dtkComposerNodeControl::value();

    qDebug() << DTK_PRETTY_FUNCTION << "value is" << value;

    if(!value.isValid())
        return;

    int i = 0;

    for(int i = 0; i < d->block_cases.count(); i++) {

        dtkComposerNodeControlBlock *block = d->block_cases.at(i);

        qDebug() << DTK_PRETTY_FUNCTION << "Checking" << block->title() << "block";

        dtkComposerNodeProperty *property = this->inputProperty(block->title(), "constant");

        if(!property)
            continue;

        if(!property->edge())
            continue;

        QVariant constant = property->edge()->source()->node()->value(property->edge()->source());

        qDebug() << DTK_PRETTY_FUNCTION << "constant is" << constant;

        if(constant == value) {
            foreach(dtkComposerNode *node, block->startNodes())
                node->update();

            matched = i;
        }
    }
    
    qDebug() << DTK_PRETTY_FUNCTION << "matched block" << matched;

    if(matched < 0)
        foreach(dtkComposerNode *node, d->block_default->startNodes())
            node->update();

    this->setDirty(false);

    if(matched >= 0) {

        dtkComposerNodeControlBlock *matched_block = d->block_cases.at(matched);

        qDebug() << DTK_PRETTY_FUNCTION << "matched block is" << matched_block->title();
        qDebug() << DTK_PRETTY_FUNCTION << "case node has" << this->outputEdges().count() << "output edges";

        foreach(dtkComposerEdge *edge, this->outputEdges()) {

            qDebug() << DTK_PRETTY_FUNCTION << "Examinating edge" << edge;

            if (edge->source() == this->outputProperty(matched_block->title(), "constant")) {

                qDebug() << DTK_PRETTY_FUNCTION << "Matched edge" << edge << edge->destination()->node();
                
                edge->destination()->node()->update();
            }
        }
    }
}

//! Overloads output value to feed the destination back with the corresponding input value.
/*! 
 * 
 * \param property Output constant property of a case block.
 */

QVariant dtkComposerNodeCase::value(dtkComposerNodeProperty *property)
{
    qDebug() << DTK_PRETTY_FUNCTION;

    foreach(dtkComposerNodeProperty *p, this->inputProperties())
        if(p->blockedFrom() == property->blockedFrom())
            if(p->edge())
                return p->edge()->source()->node()->value(p->edge()->source());

    return QVariant();
}
