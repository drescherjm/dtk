/* dtkComposerNodeProperty.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:23:07 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Dec 13 15:44:00 2010 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 88
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
        Output
    };
    
    enum Multiplicity {
        Null,
        Single,
        Multiple
    };

     dtkComposerNodeProperty(QString name, Type type, Multiplicity multiplicity, dtkComposerNode *parent);
    ~dtkComposerNodeProperty(void);

    dtkComposerNodeProperty *clone(dtkComposerNode *node = 0);

    dtkComposerEdge *edge(void);
    dtkComposerNode *node(void);

    QString name(void) const;

            Type type(void);
    Multiplicity multiplicity(void);

    int count(void);

    void hide(void);
    void show(void);

    dtkComposerNode *clonedFrom(void);
    void setClonedFrom(dtkComposerNode *node);

    bool  isDisplayed(void);
    void setDisplayed(bool dirty);

    bool  isDirty(void);
    void setDirty(bool dirty);

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

#endif
