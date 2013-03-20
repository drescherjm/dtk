
/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEVECTORREALOPERATORMODIFIER_H
#define DTKCOMPOSERNODEVECTORREALOPERATORMODIFIER_H


#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifier interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorModifierPrivate;

class  dtkComposerNodeVectorRealOperatorModifier : public dtkComposerNodeLeaf
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

class  dtkComposerNodeVectorRealOperatorModifierAll : public dtkComposerNodeLeaf
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

class  dtkComposerNodeVectorRealOperatorModifierPart : public dtkComposerNodeLeaf
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

class  dtkComposerNodeVectorRealOperatorModifierSet : public dtkComposerNodeVectorRealOperatorModifier
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

class  dtkComposerNodeVectorRealOperatorModifierSum : public dtkComposerNodeVectorRealOperatorModifier
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

class  dtkComposerNodeVectorRealOperatorModifierSubstract : public dtkComposerNodeVectorRealOperatorModifier
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

class  dtkComposerNodeVectorRealOperatorModifierMult : public dtkComposerNodeVectorRealOperatorModifier
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

class  dtkComposerNodeVectorRealOperatorModifierDivide : public dtkComposerNodeVectorRealOperatorModifier
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

class  dtkComposerNodeVectorRealOperatorModifierAllAdd : public dtkComposerNodeVectorRealOperatorModifierAll
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

class  dtkComposerNodeVectorRealOperatorModifierAllSubstract : public dtkComposerNodeVectorRealOperatorModifierAll
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

class  dtkComposerNodeVectorRealOperatorModifierAllMult : public dtkComposerNodeVectorRealOperatorModifierAll
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

class  dtkComposerNodeVectorRealOperatorModifierAllDivide: public dtkComposerNodeVectorRealOperatorModifierAll
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

class  dtkComposerNodeVectorRealOperatorModifierPartSum: public dtkComposerNodeVectorRealOperatorModifierPart
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

class  dtkComposerNodeVectorRealOperatorModifierPartSubstract: public dtkComposerNodeVectorRealOperatorModifierPart
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
