/* dtkComposerNodeBoolean.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
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

class dtkComposerNodeBooleanPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeBoolean : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeBoolean(void);
    ~dtkComposerNodeBoolean(void);

public:
    void run(void);

public:
    /* inline QString type(void) { */
    /*     return this->nodeMetaData()->type(); */
    /*     return "boolean"; */
    /* } */

    /* inline QString titleHint(void) { */
    /*     return "Boolean"; */
    /* } */

    inline QString inputLabelHint(int) {
        return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

public:
    bool value(void);

public:
    void setValue(bool value);

private:
    dtkComposerNodeBooleanPrivate *d;
};
