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

#include "dtkComposerNodeFactory.h"

class DTKCOMPOSER_EXPORT dtkComposerFactory : public dtkComposerNodeFactory
{
public:
     dtkComposerFactory(void);
    ~dtkComposerFactory(void);

public:
    void initNodeBase(void);
    void initNodeBoolean(void);
    void initNodeControl(void);
    void initNodeConstants(void);
    void initNodeDistributed(void);
    void initNodeFile(void);
    void initNodeNumber (void);
    void initNodeString (void);
    void initNodeContainer(void);

public:
    static dtkComposerFactory *instance(void);

private:
    static dtkComposerFactory *s_instance;

};

//
// dtkComposerFactory.h ends here
