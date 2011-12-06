/* dtkComposerNodeComposite.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Dec  6 14:01:34 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Dec  6 16:15:47 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 108
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode_p.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProperty.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeCompositeLabel
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCompositeLabel : public QGraphicsTextItem
{
public:
     dtkComposerNodeCompositeLabel(dtkComposerNodeComposite *parent = 0);
    ~dtkComposerNodeCompositeLabel(void);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    dtkComposerNodeComposite *node;
};

dtkComposerNodeCompositeLabel::dtkComposerNodeCompositeLabel(dtkComposerNodeComposite *parent) : QGraphicsTextItem(parent)
{
    this->node = parent;

#if defined(Q_WS_MAC)
    QFont font("Lucida Grande", 11);
#else
    QFont font("Lucida Grande", 9);
#endif

    this->setDefaultTextColor(Qt::lightGray);
    this->setFont(font);
    this->setTextInteractionFlags(Qt::TextEditorInteraction);
    this->setTextWidth(130);
    this->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
}

dtkComposerNodeCompositeLabel::~dtkComposerNodeCompositeLabel(void)
{

}

void dtkComposerNodeCompositeLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath s_rect; s_rect.addRect(QRectF(option->rect.topLeft(), QSizeF(option->rect.width(), option->rect.height() / 2)));
    QPainterPath r_rect; r_rect.addRoundedRect(option->rect, 5, 5);
    QPainterPath path = s_rect.united(r_rect);

    painter->save();
    painter->setPen(Qt::darkGray);
    painter->setBrush(Qt::black);
    painter->drawPath(path);
    painter->restore();

    QStyleOptionGraphicsItem *o = const_cast<QStyleOptionGraphicsItem*>(option);
    o->state &= ~QStyle::State_Selected;
    o->state &= ~QStyle::State_HasFocus;

    QGraphicsTextItem::paint(painter, option, widget);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeCompositeButton
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCompositeButton : public QGraphicsItem
{
public:
     dtkComposerNodeCompositeButton(dtkComposerNodeComposite *parent = 0);
    ~dtkComposerNodeCompositeButton(void);

    QRectF boundingRect(void) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeCompositeLabel *label;

    QString text;

    bool left;
    bool right;
    bool both;

private:
    dtkComposerNodeComposite *node;
};

dtkComposerNodeCompositeButton::dtkComposerNodeCompositeButton(dtkComposerNodeComposite *parent) : QGraphicsItem(parent)
{
    this->node = parent;
    this->label = NULL;

    this->left = false;
    this->right = false;
    this->both = false;

    this->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
}

dtkComposerNodeCompositeButton::~dtkComposerNodeCompositeButton(void)
{

}

QRectF dtkComposerNodeCompositeButton::boundingRect(void) const
{
    if (this->both)
        return QRectF(0, 0, 50, 11);

    return QRectF(0, 0, 20, 11);
}

void dtkComposerNodeCompositeButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath s_rect;
    QPainterPath r_rect;
    QPainterPath path;

    if (!this->both) {

        if (this->text == "+") {
            s_rect.addRect(QRectF(option->rect.topLeft(), QSizeF(option->rect.width(), option->rect.height() / 2)));
            r_rect.addRoundedRect(option->rect, 5, 5);
            path = s_rect.united(r_rect);
        }
        if (this->text == "-") {
            s_rect.addRect(QRectF(option->rect.topLeft(), QSizeF(option->rect.width(), option->rect.height())));
            path = s_rect;
        }

    } else {

        s_rect.addRect(QRectF(option->rect.topLeft(), QSizeF(option->rect.width(), option->rect.height() / 2)));
        r_rect.addRoundedRect(option->rect, 5, 5);
        path = s_rect.united(r_rect);

    }

    painter->save();
    painter->setPen(Qt::darkGray);
    painter->setBrush(Qt::black);
    painter->drawPath(path);
    painter->restore();
    
#if defined(Q_WS_MAC)
    QFont font("Lucida Grande", 8);
#else
    QFont font("Lucida Grande", 6);
#endif
    font.setBold(true);

    QFontMetrics metrics(font);
    
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, this->text);
}

void dtkComposerNodeCompositeButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if (!this->label)
        return;

    if (this->label->toPlainText().isEmpty()) {
        qDebug() << "Please enter a valid name for the new property.";
        return;
    }

    if (this->text == "+") {

        if (this->left) {

            this->node->g->appendLeftProperty(new dtkComposerNodeProperty(this->label->toPlainText(), dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsRelay, dtkComposerNodeProperty::Multiple, this->node));

        } else if (this->right) { 

            this->node->g->appendRightProperty(new dtkComposerNodeProperty(this->label->toPlainText(), dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsRelay, dtkComposerNodeProperty::Multiple, this->node));

        } else if (this->both) {          

            this->node->g->appendLeftProperty(new dtkComposerNodeProperty(this->label->toPlainText(), dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsRelay, dtkComposerNodeProperty::Multiple, this->node));
            this->node->g->appendRightProperty(new dtkComposerNodeProperty(this->label->toPlainText(), dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsRelay, dtkComposerNodeProperty::Multiple, this->node));
        }

    } else if (this->text == "-") {

        if (this->left) {

            this->node->g->removeLeftProperty(this->node->g->leftProperty(this->label->toPlainText()));

        } else if (this->right) {

            this->node->g->removeRightProperty(this->node->g->rightProperty(this->label->toPlainText()));

        } else if (this->both) {            

            this->node->g->removeLeftProperty(this->node->g->leftProperty(this->label->toPlainText()));
            this->node->g->removeRightProperty(this->node->g->rightProperty(this->label->toPlainText()));
        }
    }
    
    this->node->touch();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeCompositePrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCompositePrivate
{
public:
    dtkComposerNodeCompositeButton *button_add_left;
    dtkComposerNodeCompositeButton *button_rem_left;
    dtkComposerNodeCompositeButton *button_add_right;
    dtkComposerNodeCompositeButton *button_rem_right;
    dtkComposerNodeCompositeButton *button_add_both;
    dtkComposerNodeCompositeButton *button_rem_both;
    dtkComposerNodeCompositeLabel  *label;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeComposite
// /////////////////////////////////////////////////////////////////

dtkComposerNodeComposite::dtkComposerNodeComposite(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeCompositePrivate)
{
    static int count = 0;

    d->button_add_left = new dtkComposerNodeCompositeButton(this);
    d->button_add_left->setZValue(this->zValue() - 1);
    d->button_add_left->setVisible(false);
    d->button_add_left->left = true;

    d->button_rem_left = new dtkComposerNodeCompositeButton(this);
    d->button_rem_left->setZValue(this->zValue() - 1);
    d->button_rem_left->setVisible(false);
    d->button_rem_left->left = true;

    d->button_add_right = new dtkComposerNodeCompositeButton(this);
    d->button_add_right->setZValue(this->zValue() - 1);
    d->button_add_right->setVisible(false);
    d->button_add_right->right = true;

    d->button_rem_right = new dtkComposerNodeCompositeButton(this);
    d->button_rem_right->setZValue(this->zValue() - 1);
    d->button_rem_right->setVisible(false);
    d->button_rem_right->right = true;

    d->button_add_both = new dtkComposerNodeCompositeButton(this);
    d->button_add_both->setZValue(this->zValue() - 1);
    d->button_add_both->setVisible(false);
    d->button_add_both->both = true;

    d->button_rem_both = new dtkComposerNodeCompositeButton(this);
    d->button_rem_both->setZValue(this->zValue() - 1);
    d->button_rem_both->setVisible(false);
    d->button_rem_both->both = true;

    d->label = new dtkComposerNodeCompositeLabel(this);
    d->label->setZValue(this->zValue() - 1);
    d->label->setVisible(false);

    if(d->button_add_left)
        if(!d->button_add_left->label)
            d->button_add_left->label = d->label;

    if(d->button_rem_left)
        if(!d->button_rem_left->label)
            d->button_rem_left->label = d->label;

    if(d->button_add_right)
        if(!d->button_add_right->label)
            d->button_add_right->label = d->label;

    if(d->button_rem_right)
        if(!d->button_rem_right->label)
            d->button_rem_right->label = d->label;

    if(d->button_add_both)
        if(!d->button_add_both->label)
            d->button_add_both->label = d->label;

    if(d->button_rem_both)
        if(!d->button_rem_both->label)
            d->button_rem_both->label = d->label;

    this->setKind(dtkComposerNode::Composite);
    this->setType("dtkComposerNodeComposite");
    this->setTitle(QString("Composite node %1").arg(++count));
}

dtkComposerNodeComposite::~dtkComposerNodeComposite(void)
{
    delete d;

    d = NULL;
}

/*

void dtkComposerNodeComposite::setGhost(bool ghost)
{
    dtkComposerNode::setGhost(ghost);

    d->button_add_left->setVisible(ghost);
    d->button_rem_left->setVisible(ghost);
    d->button_add_right->setVisible(ghost);
    d->button_rem_right->setVisible(ghost);
    d->button_add_both->setVisible(ghost);
    d->button_rem_both->setVisible(ghost);
    d->label->setVisible(ghost);
}

void dtkComposerNodeComposite::layout(void)
{
    dtkComposerNode::layout();

    // QRectF rect = dtkComposerNode::d->ghostRect();

    // qDebug() << rect;
}

*/
