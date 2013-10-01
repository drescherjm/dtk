/* @(#)dtkComposerNodeStringOperator.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/20 14:34:00

 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODESTRINGOPERATOR_H
#define DTKCOMPOSERNODESTRINGOPERATOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorUnaryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeStringOperatorUnary : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeStringOperatorUnary(void);
    ~dtkComposerNodeStringOperatorUnary(void);

    inline QString inputLabelHint(int) {
        return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeStringOperatorUnaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorBinaryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeStringOperatorBinary : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeStringOperatorBinary(void);
    ~dtkComposerNodeStringOperatorBinary(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "lhs";
        else if (port == 1)
            return "rhs";
        else
            return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeStringOperatorBinaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinaryLogic
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorBinaryLogicPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeStringOperatorBinaryLogic : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeStringOperatorBinaryLogic(void);
    ~dtkComposerNodeStringOperatorBinaryLogic(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "lhs";
        else if (port == 1)
            return "rhs";
        else
            return "port";
    }

    inline QString outputLabelHint(int) {
        return "boolean";
    }

protected:
    dtkComposerNodeStringOperatorBinaryLogicPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinary - Append
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeStringOperatorBinaryAppend : public dtkComposerNodeStringOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "append";
    }

    inline QString titleHint(void) {
        return "String Append";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinaryLogic - Equality
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeStringOperatorBinaryLogicEquality : public dtkComposerNodeStringOperatorBinaryLogic
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "string_equality";
    }

    inline QString titleHint(void) {
        return "String equality";
    }
};









// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringListAppend
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringListAppendPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeStringListAppend : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeStringListAppend(void);
    ~dtkComposerNodeStringListAppend(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "list";
        else if (port == 1)
            return "string";
        return "port";
    }

    inline QString outputLabelHint(int) {
        return "list";
    }

public:
    void run(void);

public:
    inline QString type(void) {
        return "appendStringList";
    }

    inline QString titleHint(void) {
        return "Append to String List";
    }

protected:
    dtkComposerNodeStringListAppendPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringListExtract
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringListExtractPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeStringListExtract : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeStringListExtract(void);
    ~dtkComposerNodeStringListExtract(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "list";
        else if (port == 1)
            return "index";
        return "port";
    }

    inline QString outputLabelHint(int) {
        return "string";
    }

public:
    void run(void);

public:
    inline QString type(void) {
        return "extractStringList";
    }

    inline QString titleHint(void) {
        return "Extract from String List";
    }
protected:
    dtkComposerNodeStringListExtractPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringListSet
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringListSetPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeStringListSet : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeStringListSet(void);
    ~dtkComposerNodeStringListSet(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "list";
        else if (port == 1)
            return "index";
        else if (port == 2)
            return "string";
        return "port";
    }

    inline QString outputLabelHint(int) {
        return "list";
    }

public:
    void run(void);

public:
    inline QString type(void) {
        return "setStringList";
    }

    inline QString titleHint(void) {
        return "Set String List item";
    }
protected:
    dtkComposerNodeStringListSetPrivate *d;
};


#endif /* DTKCOMPOSERNODESTRINGOPERATOR_H */

