/* @(#)dtkComposerExtension.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/02/09 14:13:42
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerExport.h"

#include <dtkCore/dtkCorePlugin.h>

class dtkComposerNodeFactory;

class DTKCOMPOSER_EXPORT dtkComposerExtension
{
public:
             dtkComposerExtension(void) {}
    virtual ~dtkComposerExtension(void) {}

public:
    virtual void extend(dtkComposerNodeFactory *factory) = 0;
};

DTK_DECLARE_PLUGIN(dtkComposerExtension, DTKCOMPOSER_EXPORT)
DTK_DECLARE_PLUGIN_FACTORY(dtkComposerExtension, DTKCOMPOSER_EXPORT)
DTK_DECLARE_PLUGIN_MANAGER(dtkComposerExtension, DTKCOMPOSER_EXPORT)



