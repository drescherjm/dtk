/* dtkComposerNodeString.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 27 15:08:06 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 24 14:39:48 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 31
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

    const QString value(void);

public:
    void setEditorText(const QString& value);

public:
    void expand(void);
    void collapse(void);

public slots:
    void touch(void);

protected slots:
    void onCollapseFinised(void);

protected:
    void pull(dtkComposerEdge *route, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerEdge *route, dtkComposerNodeProperty *property);

public:
    dtkComposerNodeAbstractTransmitter *emitter(dtkComposerNodeProperty *property);

public:
    bool onLeftRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *destination);
    bool onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeStringPrivate *d;
};

#endif
