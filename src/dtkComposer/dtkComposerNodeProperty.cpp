/* dtkComposerNodeProperty.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:26:05 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  7 16:45:11 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 61
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"
#include "dtkComposerNodeProperty.h"

class dtkComposerNodePropertyPrivate
{
public:
    dtkComposerNode *parent;
    dtkComposerNodeProperty::Type type;

    QGraphicsEllipseItem *ellipse;
    QGraphicsTextItem *text;
};

dtkComposerNodeProperty::dtkComposerNodeProperty(Type type, dtkComposerNode *parent) : QObject(), QGraphicsItemGroup(parent), d(new dtkComposerNodePropertyPrivate)
{
    d->type = type;
    d->parent = parent;

    d->text = new QGraphicsTextItem(this);
    d->text->setFont(QFont("Lucida Grande", 11));
    d->text->setPlainText("Property");
    d->text->setDefaultTextColor(Qt::black);

    d->ellipse = new QGraphicsEllipseItem(this);
    d->ellipse->setPen(QPen(Qt::darkGray, 1));
}

dtkComposerNodeProperty::~dtkComposerNodeProperty(void)
{
    delete d;

    d = NULL;
}

dtkComposerNodeProperty::Type dtkComposerNodeProperty::type(void)
{
    return d->type;
}

void dtkComposerNodeProperty::setText(const QString& text)
{
    d->text->setPlainText(text);
}

void dtkComposerNodeProperty::setRect(const QRectF& rect)
{
    QFontMetrics fm(d->text->font());

    d->ellipse->setRect(rect);

    switch(d->type) {
    case Input:
        d->ellipse->setBrush(Qt::yellow);
        d->text->setPos(rect.topRight() + QPointF(0, fm.height()/2*-1));
        break;
    case Output:
        d->ellipse->setBrush(Qt::red);
        d->text->setPos(rect.topLeft() + QPointF(fm.width(d->text->toPlainText())*-1 - d->ellipse->rect().width(), fm.height()/2*-1));
        break;
    default:
        break;
    };    
}
