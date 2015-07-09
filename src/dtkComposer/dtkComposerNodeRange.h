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
#include "dtkComposerNodeLeaf.h"

class DTKCOMPOSER_EXPORT dtkComposerNodeRange : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeRange(void);
    ~dtkComposerNodeRange(void);

public slots:
    void setValue(int);

public:
    void run(void);

public:
    dtkComposerViewWidget *widget(void);

private:
    class dtkComposerNodeRangePrivate *d;
};

//
// dtkComposerNodeRange.h ends here
