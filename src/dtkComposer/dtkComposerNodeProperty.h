/* dtkComposerNodeProperty.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:23:07 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Sep  8 13:24:49 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 35
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEPROPERTY_H
#define DTKCOMPOSERNODEPROPERTY_H

#include <QtCore>
#include <QtGui>

class dtkComposerEdge;
class dtkComposerNode;
class dtkComposerNodePropertyPrivate;

class dtkComposerNodeProperty : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    enum Type  { Input, Output };

     dtkComposerNodeProperty(Type type, dtkComposerNode *parent);
    ~dtkComposerNodeProperty(void);

    dtkComposerEdge *edge(void);
    dtkComposerNode *node(void);

    Type type(void);

    int count(void);

public:
    QRectF boundingRect(void) const;
    QRectF rect(void) const;

    void setText(const QString& text);
    void setRect(const QRectF& rect);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    dtkComposerNodePropertyPrivate *d;
};

#endif
