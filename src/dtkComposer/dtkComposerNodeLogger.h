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

#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeLoggerPrivate;

class  dtkComposerNodeLogger : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeLogger(void);
    ~dtkComposerNodeLogger(void);

public:
    void run(void);

private:
    dtkComposerNodeLoggerPrivate *d;
};

// 
// dtkComposerNodeLogger.h ends here
