/* @(#)dtkComposerDefaultExtensions.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/05/04 12:47:16
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerExport.h"
#include "dtkComposerExtension.h"
#include "dtkComposerNodeFactory.h"

#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeBooleanOperator.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeConstants.h"
#include "dtkComposerNodeControlCase.h"
#include "dtkComposerNodeControlDoWhile.h"
#include "dtkComposerNodeControlFor.h"
#include "dtkComposerNodeControlForEach.h"
#include "dtkComposerNodeControlIf.h"
#include "dtkComposerNodeControlMap.h"
#include "dtkComposerNodeControlWhile.h"
#include "dtkComposerNodeDistributed.h"
#include "dtkComposerNodeExec.h"
#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeRange.h"
#include "dtkComposerNodeMetaContainer.h"
#include "dtkComposerNodeNumberOperator.h"
#include "dtkComposerNodeReal.h"
#include "dtkComposerNodeRemote.h"
#include "dtkComposerNodeSpawn.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerNodeStringOperator.h"

#include "dtkComposerNodeLogger.h"
#include "dtkComposerNodePrint.h"

// -- Base nodes

class DTKCOMPOSER_EXPORT dtkComposerBaseExtension : public dtkComposerExtension
{
public:
     dtkComposerBaseExtension(void) {};
    ~dtkComposerBaseExtension(void) {};

public:
    void extend(dtkComposerNodeFactory *factory);
};

// -- Files nodes

class DTKCOMPOSER_EXPORT dtkComposerFileExtension : public dtkComposerExtension
{
public:
     dtkComposerFileExtension(void) {};
    ~dtkComposerFileExtension(void) {};

public:
    void extend(dtkComposerNodeFactory *factory);
};

// -- Distributed nodes

class DTKCOMPOSER_EXPORT dtkComposerDistributedExtension : public dtkComposerExtension
{
public:
     dtkComposerDistributedExtension(void) {};
    ~dtkComposerDistributedExtension(void) {};

public:
    void extend(dtkComposerNodeFactory *factory);
};

// -- Constants nodes

class DTKCOMPOSER_EXPORT dtkComposerConstantsExtension : public dtkComposerExtension
{
public:
     dtkComposerConstantsExtension(void) {};
    ~dtkComposerConstantsExtension(void) {};

public:
    void extend(dtkComposerNodeFactory *factory);
};

// -- Control nodes

class DTKCOMPOSER_EXPORT dtkComposerControlExtension : public dtkComposerExtension
{
public:
     dtkComposerControlExtension(void) {};
    ~dtkComposerControlExtension(void) {};

public:
    void extend(dtkComposerNodeFactory *factory);
};

// -- Boolean nodes

class DTKCOMPOSER_EXPORT dtkComposerBooleanExtension : public dtkComposerExtension
{
public:
     dtkComposerBooleanExtension(void) {};
    ~dtkComposerBooleanExtension(void) {};

public:
    void extend(dtkComposerNodeFactory *factory);
};

// -- Number nodes

class DTKCOMPOSER_EXPORT dtkComposerNumberExtension : public dtkComposerExtension
{
public:
     dtkComposerNumberExtension(void) {};
    ~dtkComposerNumberExtension(void) {};

public:
    void extend(dtkComposerNodeFactory *factory);
};

// -- String nodes

class DTKCOMPOSER_EXPORT dtkComposerStringExtension : public dtkComposerExtension
{
public:
     dtkComposerStringExtension(void) {};
    ~dtkComposerStringExtension(void) {};

public:
    void extend(dtkComposerNodeFactory *factory);
};

// -- Containers nodes

class DTKCOMPOSER_EXPORT dtkComposerContainerExtension : public dtkComposerExtension
{
public:
     dtkComposerContainerExtension(void) {};
    ~dtkComposerContainerExtension(void) {};

public:
    void extend(dtkComposerNodeFactory *factory);
};
