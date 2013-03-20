/* dtkComposerNodeArrayDataOperatorModifier.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jul  5 09:00:34 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jul  5 12:18:22 2012 (+0200)
 *           By: tkloczko
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEARRAYDATAOPERATORMODIFIER_H
#define DTKCOMPOSERNODEARRAYDATAOPERATORMODIFIER_H


#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataOperatorModifier interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayDataOperatorModifierPrivate;

class  dtkComposerNodeArrayDataOperatorModifier : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeArrayDataOperatorModifier(void);
    ~dtkComposerNodeArrayDataOperatorModifier(void);

public:
    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "array";
        else if (port == 1)
            return "index";
        else
            return "item";
    }

    inline QString outputLabelHint(int) {
        return "array";
    }

protected:
    dtkComposerNodeArrayDataOperatorModifierPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataOperatorModifierAll interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayDataOperatorModifierAllPrivate;

class  dtkComposerNodeArrayDataOperatorModifierAll  : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeArrayDataOperatorModifierAll(void);
    ~dtkComposerNodeArrayDataOperatorModifierAll (void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "array";
        else
            return "item";
    }

    inline QString outputLabelHint(int) {
        return "array";
    }

protected:
    dtkComposerNodeArrayDataOperatorModifierAllPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataOperator - INSERT
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayDataOperatorInsert : public dtkComposerNodeArrayDataOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_data_insert";
    }

    inline QString titleHint(void) {
        return "Data array insert";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataOperator - Set
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayDataOperatorSet : public dtkComposerNodeArrayDataOperatorModifier
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_data_set";
    }

    inline QString titleHint(void) {
        return "Data array set";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataOperator - APPEND
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayDataOperatorAppend : public dtkComposerNodeArrayDataOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_data_append";
    }

    inline QString titleHint(void) {
        return "Data array append";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataOperatorModifierALL - PREPEND
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayDataOperatorPrepend : public dtkComposerNodeArrayDataOperatorModifierAll
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "array_data_prepend";
    }

    inline QString titleHint(void) {
        return "Data array prepend";
    }
};

#endif
