// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include "dtkComposerExport.h"
#include "dtkComposerNodeBoolean_p.h"
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
    bool value(void);

public:
    void setValue(bool value);

public:
    dtkComposerNodeBooleanEditor *editor(void);

private:
    dtkComposerNodeBooleanPrivate *d;
};

//
// dtkComposerNodeBoolean.h ends here
