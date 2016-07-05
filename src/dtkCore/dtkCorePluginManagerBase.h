/* @(#)dtkCorePluginManagerBase.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/07/04 14:04:27
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkCoreExport.h"

#include <QtCore>

class DTKCORE_EXPORT dtkCorePluginManagerBase
{
public:
    static dtkCorePluginManagerBase* instance(void) ;

public:
    QHash<QString, QVariant> names;
    QHash<QString, QVariant> versions;
    QHash<QString, QVariant> concept;

private:
    static dtkCorePluginManagerBase *s_instance;
};
