/* dtkComposerNodeConditional.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:59:35 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr 27 17:27:04 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONDITIONAL_H
#define DTKCOMPOSERNODECONDITIONAL_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeControl.h"

class dtkComposerEdge;
class dtkComposerNodeProperty;

class dtkComposerNodeConditionalPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeConditional : public dtkComposerNodeControl
{
    Q_OBJECT

public:
     dtkComposerNodeConditional(dtkComposerNode *parent = 0);
    ~dtkComposerNodeConditional(void);

public:
    void layout(void);

public slots:
    void update(void);

protected:
    void pull(dtkComposerEdge *i_route, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerEdge *o_route, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeConditionalPrivate *d;
};

#endif
