/* dtkComposerNodeProperty.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:23:07 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Mar 15 10:56:47 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 123
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEPROPERTY_H
#define DTKCOMPOSERNODEPROPERTY_H

#include "dtkComposerExport.h"

#include <QtCore>
#include <QtDebug>
#include <QtGui>

class dtkComposerEdge;
class dtkComposerNode;
class dtkComposerNodePropertyPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeProperty : public QObject, public QGraphicsItem
{
    Q_OBJECT

#if QT_VERSION >= 0x040600
    Q_INTERFACES(QGraphicsItem)
#endif

public:
    enum Type {
        Input,
        Output,
        HybridInput,
        HybridOutput
    };
    
    enum Multiplicity {
        Null,
        Single,
        Multiple
    };

    enum Behavior {
        None,
        AsRelay,
        AsInput,
        AsOutput
    };

     dtkComposerNodeProperty(QString name, Type type, Multiplicity multiplicity, dtkComposerNode *parent);
    ~dtkComposerNodeProperty(void);

    QString description(void);    

    dtkComposerNodeProperty *clone(dtkComposerNode *node = 0);

    dtkComposerEdge *edge(void);
    dtkComposerNode *node(void);

    QString name(void) const;

            Type type(void);
    Multiplicity multiplicity(void);
        Behavior behavior(void);

    bool contains(const QPointF& point) const;

    int count(void);

    void hide(void);
    void show(void);

    dtkComposerNode *parent(void);
    dtkComposerNode *clonedFrom(void);
    
    QString blockedFrom(void) const;

    void setBlockedFrom(const QString& name);
    void setClonedFrom(dtkComposerNode *node);
    void setParentNode(dtkComposerNode *node);

    bool  isDisplayed(void);
    void setDisplayed(bool dirty);

    void setName(const QString& name);

    void setBehavior(Behavior behavior);

    friend QDebug operator<<(QDebug dbg, dtkComposerNodeProperty& property);
    friend QDebug operator<<(QDebug dbg, dtkComposerNodeProperty *property);

public:
    QRectF boundingRect(void) const;
    QRectF         rect(void) const;

    void setText(const QString& text);
    void setRect(const QRectF& rect);

    void mirror(void);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    dtkComposerNodePropertyPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

QDebug operator<<(QDebug dbg, dtkComposerNodeProperty  property);
QDebug operator<<(QDebug dbg, dtkComposerNodeProperty& property);
QDebug operator<<(QDebug dbg, dtkComposerNodeProperty *property);

#endif
