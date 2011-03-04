/* dtkComposerNodeControlBlock.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Mar  3 14:48:10 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar  3 18:15:04 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 41
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"
#include "dtkComposerNodeControlBlock.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlBlockPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlBlockPrivate
{
public:
    QColor color;
    QString title;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlBlock
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlBlock::dtkComposerNodeControlBlock(const QString& title, QGraphicsItem *parent) : QGraphicsRectItem(parent), d(new dtkComposerNodeControlBlockPrivate)
{
    d->color = QColor("#c7c7c7");
    d->title = title;

    this->setPen(d->color);
    this->setBrush(Qt::NoBrush);
}

dtkComposerNodeControlBlock::~dtkComposerNodeControlBlock(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeControlBlock::title(void) const
{
    return d->title;
}

QColor dtkComposerNodeControlBlock::penColor(void) const
{
    return d->color;
}

void dtkComposerNodeControlBlock::setPenColor(const QColor& color)
{
    d->color = color;

    this->setPen(d->color);
    this->update();
}

QList<dtkComposerNode *> dtkComposerNodeControlBlock::nodes(void)
{
    QList<dtkComposerNode *> nodes;

    foreach(QGraphicsItem *item, this->childItems())
        if(dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item))
            nodes << node;

    return nodes;
}

QList<dtkComposerNode *> dtkComposerNodeControlBlock::startNodes(void)
{
    QList<dtkComposerNode *> nodes;

    foreach(dtkComposerNode *node, this->nodes())
        if(node->inputEdges().count() == 0)
            nodes << node;

    return nodes;
}

QList<dtkComposerNode *> dtkComposerNodeControlBlock::endNodes(void)
{
    QList<dtkComposerNode *> nodes;

    foreach(dtkComposerNode *node, this->nodes())
        if(node->outputEdges().count() == 0)
            nodes << node;

    return nodes;
}

void dtkComposerNodeControlBlock::highlight(void)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "penColor");
    animation->setDuration(1000);
    animation->setKeyValueAt(0.0, QColor("#c7c7c7"));
    animation->setKeyValueAt(0.1, Qt::red);
    animation->setKeyValueAt(0.2, QColor("#c7c7c7"));
    animation->setKeyValueAt(0.3, Qt::red);
    animation->setKeyValueAt(0.4, QColor("#c7c7c7"));
    animation->setKeyValueAt(0.5, Qt::red);
    animation->setKeyValueAt(0.6, QColor("#c7c7c7"));
    animation->setKeyValueAt(0.7, Qt::red);
    animation->setKeyValueAt(0.8, QColor("#c7c7c7"));
    animation->setKeyValueAt(0.9, Qt::red);
    animation->setKeyValueAt(1.0, QColor("#c7c7c7"));
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
