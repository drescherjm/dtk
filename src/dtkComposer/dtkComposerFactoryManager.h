/* dtkComposerFactoryManager.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/05/02 08:04:58
 */

#pragma once

#include "dtkComposerExport.h"
#include "dtkComposerNodeFactory.h"

class dtkComposerFactoryManagerPrivate;

class DTKCOMPOSER_EXPORT dtkComposerFactoryManager
{
public:
     dtkComposerFactoryManager(void);
    ~dtkComposerFactoryManager(void);

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
    dtkComposerNodeFactory *factory(void);

private:
    dtkComposerFactoryManagerPrivate *d;

};
