/* dtkComposerNodeProperty.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:23:07 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Nov 30 09:38:44 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 71
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

    dtkComposerNodeProperty *clone(dtkComposerNode *node);

    dtkComposerEdge *edge(void);
    dtkComposerNode *node(void);

    QString name(void) const;

            Type type(void);
    Multiplicity multiplicity(void);

    int count(void);

    void hide(void);
    void show(void);

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
