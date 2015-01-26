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

#pragma once

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

protected:
    dtkComposerNodeStringOperatorUnaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorBinaryPrivate;

class DTKCOMPOSER_EXPORT  dtkComposerNodeStringOperatorBinary : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeStringOperatorBinary(void);
    ~dtkComposerNodeStringOperatorBinary(void);

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

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinaryLogic - Equality
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeStringOperatorBinaryLogicEquality : public dtkComposerNodeStringOperatorBinaryLogic
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorReplace
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringReplacePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeStringReplace : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeStringReplace(void);
    ~dtkComposerNodeStringReplace(void);

public:
    void run(void);

protected:
    dtkComposerNodeStringReplacePrivate *d;

};



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringListAppend
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringListAppendPrivate;

// FIXME: we should use a generic node for doing this

class DTKCOMPOSER_EXPORT dtkComposerNodeStringListAppend : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeStringListAppend(void);
    ~dtkComposerNodeStringListAppend(void);

public:
    void run(void);

protected:
    dtkComposerNodeStringListAppendPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringListExtract
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringListExtractPrivate;

// FIXME: we should use a generic node for doing this

class DTKCOMPOSER_EXPORT dtkComposerNodeStringListExtract : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeStringListExtract(void);
    ~dtkComposerNodeStringListExtract(void);

public:
    void run(void);

protected:
    dtkComposerNodeStringListExtractPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringListSet
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringListSetPrivate;


// FIXME: we should use a generic node for doing this

class DTKCOMPOSER_EXPORT dtkComposerNodeStringListSet : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeStringListSet(void);
    ~dtkComposerNodeStringListSet(void);

public:
    void run(void);

protected:
    dtkComposerNodeStringListSetPrivate *d;
};
