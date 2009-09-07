/* dtkComposerNodeProperty.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:23:07 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  7 15:51:32 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 15
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

class dtkComposerNode;
class dtkComposerNodePropertyPrivate;

class dtkComposerNodeProperty : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

public:
    enum Type { Input, Output };

     dtkComposerNodeProperty(Type type, dtkComposerNode *parent);
    ~dtkComposerNodeProperty(void);

    Type type(void);

public:
    void setText(const QString& text);
    void setRect(const QRectF& rect);

private:
    dtkComposerNodePropertyPrivate *d;
};

#endif
