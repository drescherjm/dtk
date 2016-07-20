/* dtkComposerScenePort.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 13:59:41 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jul 10 12:52:05 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 177
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerScenePort.h"

class dtkComposerScenePortPrivate
{
public:
    dtkComposerScenePort::Type type;

public:
    dtkComposerSceneNode *node;

public:
    int loop;

public:
    QGraphicsEllipseItem *ellipse;
    QGraphicsTextItem *label;

public:
    QString unelided;
};

dtkComposerScenePort::dtkComposerScenePort(Type type, dtkComposerSceneNode *parent) : QGraphicsItem(parent), d(new dtkComposerScenePortPrivate)
{
    d->type = type;
    d->node = parent;
    d->loop = 0;

    d->ellipse = new QGraphicsEllipseItem(this);
    d->ellipse->setPen(QPen(QColor(Qt::darkGray).darker().darker(), 1));
    d->ellipse->setBrush(Qt::lightGray);
    d->ellipse->setRect(0, 0, 10, 10);

    d->label = new QGraphicsTextItem(this);
#if defined(Q_OS_MAC)
    d->label->setFont(QFont("Lucida Grande", 11));
#else
    d->label->setFont(QFont("Lucida Grande", 9));
#endif
    d->label->setDefaultTextColor(Qt::white);

    this->setFlags(QGraphicsItem::ItemIsSelectable);
    this->setZValue(1);
}

dtkComposerScenePort::dtkComposerScenePort(Type type, const QString& label, dtkComposerSceneNode *parent) : QGraphicsItem(parent), d(new dtkComposerScenePortPrivate)
{
    d->type = type;
    d->node = parent;
    d->loop = 0;

    d->ellipse = new QGraphicsEllipseItem(this);
    d->ellipse->setPen(QPen(Qt::darkGray, 1));
    d->ellipse->setBrush(Qt::lightGray);
    d->ellipse->setRect(0, 0, 10, 10);

    d->label = new QGraphicsTextItem(this);
#if defined(Q_OS_MAC)
    d->label->setFont(QFont("Lucida Grande", 11));
#else
    d->label->setFont(QFont("Lucida Grande", 9));
#endif
    d->label->setDefaultTextColor(Qt::white);

    this->setLabel(label);
    this->setFlags(QGraphicsItem::ItemIsSelectable);
    this->setZValue(1);
}

dtkComposerScenePort::~dtkComposerScenePort(void)
{
    delete d;

    d = NULL;
}

dtkComposerScenePort::Type dtkComposerScenePort::type(void)
{
    return d->type;
}

dtkComposerSceneNode *dtkComposerScenePort::node(void)
{
    return d->node;
}

dtkComposerSceneNode *dtkComposerScenePort::owner(void)
{
    if (dynamic_cast<dtkComposerSceneNodeControl *>(d->node->parent()))
        return d->node->parent();

    return d->node;
}

int dtkComposerScenePort::loop(void)
{
    return d->loop;
}

QString dtkComposerScenePort::label(void)
{
    return d->unelided;
}

void dtkComposerScenePort::setLoop(int loop)
{
    d->loop = loop;

    if (loop > 0)
        d->ellipse->setBrush(Qt::white);
}

void dtkComposerScenePort::setLabel(const QString& label)
{
    d->unelided = label;

    QFontMetricsF fm(d->label->font());

    if (d->type == Input)
        d->label->setPlainText(fm.elidedText(d->unelided, Qt::ElideRight, 50));
    else
        d->label->setPlainText(fm.elidedText(d->unelided, Qt::ElideLeft, 50));

    if (d->type == Input)
        d->label->setPos(d->ellipse->pos() + QPointF(d->ellipse->boundingRect().width(), 0) - QPointF(0, fm.height() / 2.0));
    else
        d->label->setPos(d->ellipse->pos() - QPointF(7, 0) - QPointF(fm.width(d->label->toPlainText()), fm.height() / 2.0));

    d->ellipse->setToolTip(d->unelided);
    d->label->setToolTip(d->unelided);
}

QRectF dtkComposerScenePort::boundingRect(void) const
{
    return QRectF(0, 0, 10, 10);
}

void dtkComposerScenePort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
