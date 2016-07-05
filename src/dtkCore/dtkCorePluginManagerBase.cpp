/* @(#)dtkCorePluginManagerBase.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/07/04 14:23:33
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkCorePluginManagerBase.h"

dtkCorePluginManagerBase* dtkCorePluginManagerBase::instance(void)
{
    if(!s_instance) {
        s_instance = new dtkCorePluginManagerBase;
    }

    return s_instance;
};


dtkCorePluginManagerBase *dtkCorePluginManagerBase::s_instance = NULL;
