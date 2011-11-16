/* dtkComposerNodeString.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 27 15:08:06 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Nov 15 15:12:45 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODESTRING_H
#define DTKCOMPOSERNODESTRING_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeAbstractTransmitter;

class dtkComposerNodeStringPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeString : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeString(dtkComposerNode *parent = 0);
    ~dtkComposerNodeString(void);

    QVariant value(dtkComposerNodeProperty *property);

public:
    QString value(void);
    void setValue(QString value);

public:
    void expand(void);
    void collapse(void);

public slots:
    void touch(void);

protected slots:
    void onCollapseFinised(void);

protected:
    void pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

public:
    dtkComposerNodeAbstractTransmitter *emitter(dtkComposerNodeProperty *property);
    bool  onLeftRouteConnected(dtkComposerEdge *route);
    bool onRightRouteConnected(dtkComposerEdge *route);

private:
    dtkComposerNodeStringPrivate *d;
};

#endif
