
/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEVECTORINTEGEROPERATORMODIFIER_H
#define DTKCOMPOSERNODEVECTORINTEGEROPERATORMODIFIER_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifier interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorModifierPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorModifier : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeVectorIntegerOperatorModifier(void);
    ~dtkComposerNodeVectorIntegerOperatorModifier(void);

public:
    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "vector";
        else if (port == 1)
            return "index";
        else
            return "value";
    }

    inline QString outputLabelHint(int) {
        return "vector";
    }

protected:
    dtkComposerNodeVectorIntegerOperatorModifierPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifierAll interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorModifierAllPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorModifierAll : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeVectorIntegerOperatorModifierAll(void);
    ~dtkComposerNodeVectorIntegerOperatorModifierAll(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "vector";
        else
            return "value";
    }

    inline QString outputLabelHint(int) {
        return "vector";
    }

protected:
    dtkComposerNodeVectorIntegerOperatorModifierAllPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifierPart interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorModifierPartPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorModifierPart : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeVectorIntegerOperatorModifierPart(void);
    ~dtkComposerNodeVectorIntegerOperatorModifierPart(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "vector";
        else if (port == 1)
            return "subvector";
        else
            return "index";
    }

    inline QString outputLabelHint(int) {
        return "vector";
    }

protected:
    dtkComposerNodeVectorIntegerOperatorModifierPartPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifier - SET
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorModifierSet : public dtkComposerNodeVectorIntegerOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_integer_set";
    }

    inline QString titleHint(void) {
        return "Vector Integer Set";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifier - SUM
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorModifierSum : public dtkComposerNodeVectorIntegerOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_integer_sum";
    }

    inline QString titleHint(void) {
        return "Vector Integer Sum ";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifier - Substract
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorModifierSubstract : public dtkComposerNodeVectorIntegerOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_integer_substract";
    }

    inline QString titleHint(void) {
        return "Vector Integer Substract ";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifier - Mult
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorModifierMult : public dtkComposerNodeVectorIntegerOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_integer_mult";
    }

    inline QString titleHint(void) {
        return "Vector Integer Mult";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifier - Divide
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorModifierDivide : public dtkComposerNodeVectorIntegerOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_integer_divide";
    }

    inline QString titleHint(void) {
        return "Vector Integer Divide";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifierAll - Add
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorModifierAllAdd : public dtkComposerNodeVectorIntegerOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_integer_add_all";
    }

    inline QString titleHint(void) {
        return "Vector Integer Add All";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifierAll - Substract
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorModifierAllSubstract : public dtkComposerNodeVectorIntegerOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_integer_substract_all";
    }

    inline QString titleHint(void) {
        return "Vector Integer Substract All";
    }
};

///////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifierAll - Mult
///////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorModifierAllMult : public dtkComposerNodeVectorIntegerOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_integer_mult_all";
    }

    inline QString titleHint(void) {
        return "Vector Integer Mult All";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifierAll - Divide
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorModifierAllDivide: public dtkComposerNodeVectorIntegerOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_integer_divide_all";
    }

    inline QString titleHint(void) {
        return "Vector Integer Divide All";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifierPart - Sum
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorModifierPartSum: public dtkComposerNodeVectorIntegerOperatorModifierPart
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorIntegerOperatorModifierPartSum";
    }

    inline QString titleHint(void) {
        return "Vector Integer : Sum SubVector";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifierPart - Substract
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerOperatorModifierPartSubstract: public dtkComposerNodeVectorIntegerOperatorModifierPart
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorIntegerOperatorModifierPartSubstract";
    }

    inline QString titleHint(void) {
        return "Vector Integer : Substract SubVector";
    }
};

#endif
