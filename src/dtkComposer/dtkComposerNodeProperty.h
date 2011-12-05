/* dtkComposerNodeProperty.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:23:07 2009 (+0200)
 * Version: $Id$
<<<<<<< HEAD
 * Last-Updated: Mon Dec  5 14:10:12 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 139
=======
 * Last-Updated: Mon Dec  5 13:09:44 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 147
>>>>>>> 1de27d7fd67bf54273589ac53a89f681c90aae5b
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
        Generic,
        Input,
        Output,
        HybridInput,
        HybridOutput,
        PassThroughInput,
        PassThroughOutput
    };

    enum Position {
        Top,
        Bottom,
        Left,
        Right
    };
    
    enum Multiplicity {
        Null,
        Single,
        Multiple
    };

    enum Behavior {
        None,
        AsInput,
        AsOutput,
        AsRelay,
        AsLoop,
        AsLoopInput,
        AsLoopOutput
    };

     dtkComposerNodeProperty(QString name, Type type, Multiplicity multiplicity, dtkComposerNode *parent);
     dtkComposerNodeProperty(QString name, Position position, Behavior behavior, Multiplicity multiplicity, dtkComposerNode *parent);
    ~dtkComposerNodeProperty(void);

    QString description(void);

    dtkComposerEdge *edge(void);
    dtkComposerNode *node(void);

    QString name(void) const;

            Type type(void);
        Position position(void);
    Multiplicity multiplicity(void);
        Behavior behavior(void);

    bool contains(const QPointF& point) const;

    int count(void);

    void hide(void);
    void show(void);

    dtkComposerNode *parent(void);
    
    QString blockedFrom(void) const;

    void setBlockedFrom(const QString& name);

    void setParentNode(dtkComposerNode *node);

    bool  isDisplayed(void);
    void setDisplayed(bool dirty);

    void setName(const QString& name);

    void     setType(Type type);
    void setPosition(Position position);
    void setBehavior(Behavior behavior);

    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNodeProperty& property);
    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNodeProperty *property);

public:
    static dtkComposerNodeProperty *createCompositeProperty(dtkComposerNodeProperty *origin, dtkComposerNode *node);

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

DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNodeProperty  property);
DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNodeProperty& property);
DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNodeProperty *property);

#endif
