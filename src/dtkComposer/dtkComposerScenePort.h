/* dtkComposerScenePort.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 12:28:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 16 18:04:12 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 28
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENEPORT_H
#define DTKCOMPOSERSCENEPORT_H

#include <QtGui>

class dtkComposerScenePortPrivate;
class dtkComposerSceneNode;

class dtkComposerScenePort : public QGraphicsItem
{
public:
    enum Type { Input, Output };

public:
     dtkComposerScenePort(unsigned int id, Type type, dtkComposerSceneNode *parent);
     dtkComposerScenePort(unsigned int id, Type type, const QString& label, dtkComposerSceneNode *parent);
    ~dtkComposerScenePort(void);

public:
    unsigned int id(void) const;

public:
    Type type(void);

public:
    dtkComposerSceneNode *node(void);

public:
    QString label(void);

public:
    void setLabel(const QString& label);

public:
    virtual QRectF boundingRect(void) const;

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    dtkComposerScenePortPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerScenePortList
// /////////////////////////////////////////////////////////////////

class dtkComposerScenePortList : public QList<dtkComposerScenePort *> {};

#endif
