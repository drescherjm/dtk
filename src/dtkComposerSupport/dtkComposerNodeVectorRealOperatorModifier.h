
/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEVECTORREALOPERATORMODIFIER_H
#define DTKCOMPOSERNODEVECTORREALOPERATORMODIFIER_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifier interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorModifierPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorRealOperatorModifier : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeVectorRealOperatorModifier(void);
    ~dtkComposerNodeVectorRealOperatorModifier(void);

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
    dtkComposerNodeVectorRealOperatorModifierPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifierAll interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorModifierAllPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorRealOperatorModifierAll : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeVectorRealOperatorModifierAll(void);
    ~dtkComposerNodeVectorRealOperatorModifierAll(void);

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
    dtkComposerNodeVectorRealOperatorModifierAllPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifierPart interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorModifierPartPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorRealOperatorModifierPart : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeVectorRealOperatorModifierPart(void);
    ~dtkComposerNodeVectorRealOperatorModifierPart(void);

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
    dtkComposerNodeVectorRealOperatorModifierPartPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifier - SET
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorRealOperatorModifierSet : public dtkComposerNodeVectorRealOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_real_set";
    }

    inline QString titleHint(void) {
        return "Vector Real Set";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifier - SUM
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorRealOperatorModifierSum : public dtkComposerNodeVectorRealOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_real_sum";
    }

    inline QString titleHint(void) {
        return "Vector Real Sum ";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifier - Substract
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorRealOperatorModifierSubstract : public dtkComposerNodeVectorRealOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_real_substract";
    }

    inline QString titleHint(void) {
        return "Vector Real Substract ";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifier - Mult
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorRealOperatorModifierMult : public dtkComposerNodeVectorRealOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_real_mult";
    }

    inline QString titleHint(void) {
        return "Vector Real Mult";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifier - Divide
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorRealOperatorModifierDivide : public dtkComposerNodeVectorRealOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_real_divide";
    }

    inline QString titleHint(void) {
        return "Vector Real Divide";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifierAll - Add
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorRealOperatorModifierAllAdd : public dtkComposerNodeVectorRealOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_real_add_all";
    }

    inline QString titleHint(void) {
        return "Vector Real Add All";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifierAll - Substract
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorRealOperatorModifierAllSubstract : public dtkComposerNodeVectorRealOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_real_substract_all";
    }

    inline QString titleHint(void) {
        return "Vector Real Substract All";
    }
};

///////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifierAll - Mult
///////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorRealOperatorModifierAllMult : public dtkComposerNodeVectorRealOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_real_mult_all";
    }

    inline QString titleHint(void) {
        return "Vector Real Mult All";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifierAll - Divide
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorRealOperatorModifierAllDivide: public dtkComposerNodeVectorRealOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_real_divide_all";
    }

    inline QString titleHint(void) {
        return "Vector Real Divide All";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifierPart - Sum
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorRealOperatorModifierPartSum: public dtkComposerNodeVectorRealOperatorModifierPart
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorRealOperatorModifierPartSum";
    }

    inline QString titleHint(void) {
        return "Vector Real : Sum SubVector";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifierPart - Substract
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorRealOperatorModifierPartSubstract: public dtkComposerNodeVectorRealOperatorModifierPart
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorRealOperatorModifierPartSubstract";
    }

    inline QString titleHint(void) {
        return "Vector Real : Substract SubVector";
    }
};

#endif
