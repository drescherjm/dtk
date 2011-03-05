/* dtkComposerNodeCase.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:03:58 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Mar  5 22:00:38 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 120
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

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

    dtkComposerNodeProperty *input_constant = block->addInputProperty("constant", this);
    input_constant->setBlockedFrom(title);
    
    dtkComposerNodeProperty *output_constant = block->addOutputProperty("constant", this);
    output_constant->setBlockedFrom(title);

    this->addInputProperty(input_constant);
    this->addOutputProperty(output_constant);
    
    d->block_cases.prepend(block);

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
}
