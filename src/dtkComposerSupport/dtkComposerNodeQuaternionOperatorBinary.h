/* dtkComposerNodeQuaternionOperatorBinary.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Apr 27 14:24:47 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr 27 14:45:14 2012 (+0200)
 *           By: tkloczko
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEQUATERNIONOPERATORBINARY_H
#define DTKCOMPOSERNODEQUATERNIONOPERATORBINARY_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorBinary interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeQuaternionOperatorBinaryPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeQuaternionOperatorBinary : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeQuaternionOperatorBinary(void);
    ~dtkComposerNodeQuaternionOperatorBinary(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "quat_lhs";
        else
            return "quat_rhs";
    }

    inline QString outputLabelHint(int) {
        return "quat";
    }

protected:
    dtkComposerNodeQuaternionOperatorBinaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorHomothetic interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeQuaternionOperatorHomotheticPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeQuaternionOperatorHomothetic : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeQuaternionOperatorHomothetic(void);
    ~dtkComposerNodeQuaternionOperatorHomothetic(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "quat";
        else
            return "scalar";
    }

    inline QString outputLabelHint(int) {
        return "quat";
    }

protected:
    dtkComposerNodeQuaternionOperatorHomotheticPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorBinary - SUM 
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeQuaternionOperatorBinarySum : public dtkComposerNodeQuaternionOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "quat_sum";
    }

    inline QString titleHint(void) {
        return "Quat Sum";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorBinary - SUBSTRACT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeQuaternionOperatorBinarySubstract : public dtkComposerNodeQuaternionOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "quat_substract";
    }

    inline QString titleHint(void) {
        return "Quat Substract";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorBinary - HAMILTON MULT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeQuaternionOperatorBinaryMult : public dtkComposerNodeQuaternionOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "quat_mult";
    }

    inline QString titleHint(void) {
        return "Quat Mult";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorHomothetic - MULTIPLY
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeQuaternionOperatorHomotheticMult : public dtkComposerNodeQuaternionOperatorHomothetic
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "quat_scal_mult";
    }

    inline QString titleHint(void) {
        return "Quat: scal * quat";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorHomothetic - DIVIDE
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeQuaternionOperatorHomotheticDivision : public dtkComposerNodeQuaternionOperatorHomothetic
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "quat_scal_divide";
    }

    inline QString titleHint(void) {
        return "Quat: quat / scal";
    }
};

#endif
