/* dtkComposerNodeProperty.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:23:07 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep 10 10:28:17 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 41
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
    enum Type { Input, Output };
    enum Multiplicity { Null, Single, Multiple };

     dtkComposerNodeProperty(QString name, Type type, Multiplicity multiplicity, dtkComposerNode *parent);
    ~dtkComposerNodeProperty(void);

    dtkComposerEdge *edge(void);
    dtkComposerNode *node(void);

    Type type(void);
    Multiplicity multiplicity(void);

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
