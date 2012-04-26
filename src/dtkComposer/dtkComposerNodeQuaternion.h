/* dtkComposerNodeQuaternion.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Apr 26 13:03:34 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 13:05:26 2012 (+0200)
 *           By: tkloczko
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEQUATERNION_H
#define DTKCOMPOSERNODEQUATERNION_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeQuaternionPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeQuaternion : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeQuaternion(void);
    ~dtkComposerNodeQuaternion(void);
    
public:
    void run(void);

public:
    inline QString type(void) {
        return "quaternion";
    }

    inline QString titleHint(void) {
        return "Quaternion";
    }

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

private:
    dtkComposerNodeQuaternionPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

#include <dtkMath/dtkQuaternion>

typedef dtkQuaternion<qreal> dtkQuaternionReal;

Q_DECLARE_METATYPE(dtkQuaternionReal);
Q_DECLARE_METATYPE(dtkQuaternionReal *);

#endif
