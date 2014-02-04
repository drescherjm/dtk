/* dtkComposerNodeReal.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:40:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr  2 13:00:23 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEREAL_H
#define DTKCOMPOSERNODEREAL_H


#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeRealPrivate;

class  dtkComposerNodeReal : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeReal(void);
    ~dtkComposerNodeReal(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "real";
    }

    inline QString titleHint(void) {
        return "Real";
    }

    inline QString inputLabelHint(int port) {
        return "value";
    }

    inline QString outputLabelHint(int port) {
        return "value";
    }

public:
    qreal value(void);

public:
    void setValue(double value);

private:
    dtkComposerNodeRealPrivate *d;
};

#endif
