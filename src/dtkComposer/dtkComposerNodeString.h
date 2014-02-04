/* dtkComposerNodeString.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:50:23 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Oct  4 10:04:23 2012 (+0200)
 *           By: tkloczko
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODESTRING_H
#define DTKCOMPOSERNODESTRING_H


#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeStringPrivate;

class  dtkComposerNodeString : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeString(void);
    ~dtkComposerNodeString(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "string";
    }

    inline QString titleHint(void) {
        return "String";
    }

    inline QString inputLabelHint(int port) {
        if(port == 0)
            return "string";

        if(port == 1)
            return "real";

        return dtkComposerNodeLeaf::inputLabelHint(port);
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

public:
    QString value(void);

public:
    void setValue(QString value);

private:
    dtkComposerNodeStringPrivate *d;
};

#endif
