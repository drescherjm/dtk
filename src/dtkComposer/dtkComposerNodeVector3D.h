/* dtkComposerNodeVector3D.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Apr 26 10:10:43 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 11:34:18 2012 (+0200)
 *           By: tkloczko
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEVECTOR3D_H
#define DTKCOMPOSERNODEVECTOR3D_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeVector3DPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeVector3D : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeVector3D(void);
    ~dtkComposerNodeVector3D(void);
    
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector3D";
    }

    inline QString titleHint(void) {
        return "Vector3D";
    }

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

private:
    dtkComposerNodeVector3DPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

#include <dtkMath/dtkVector3D>

typedef dtkVector3D<qreal> dtkVector3DReal;

Q_DECLARE_METATYPE(dtkVector3DReal);
Q_DECLARE_METATYPE(dtkVector3DReal *);

#endif
