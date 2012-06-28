
/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEVECTORREALOPERATORMODIFIER_H
#define DTKCOMPOSERNODEVECTORREALOPERATORMODIFIER_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifier interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorModifierPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorModifier : public dtkComposerNodeLeaf
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

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorModifierAll  : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeVectorRealOperatorModifierAll(void);
    ~dtkComposerNodeVectorRealOperatorModifierAll (void);

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
// dtkComposerNodeVectorRealOperatorModifier - SET
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorModifierSet : public dtkComposerNodeVectorRealOperatorModifier
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

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorModifierSum : public dtkComposerNodeVectorRealOperatorModifier
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

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorModifierSubstract : public dtkComposerNodeVectorRealOperatorModifier
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

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorModifierMult : public dtkComposerNodeVectorRealOperatorModifier
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

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorModifierDivide : public dtkComposerNodeVectorRealOperatorModifier
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

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorModifierAllAdd : public dtkComposerNodeVectorRealOperatorModifierAll
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

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorModifierAllSubstract : public dtkComposerNodeVectorRealOperatorModifierAll
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

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorModifierAllMult : public dtkComposerNodeVectorRealOperatorModifierAll
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

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorModifierAllDivide: public dtkComposerNodeVectorRealOperatorModifierAll
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

#endif
