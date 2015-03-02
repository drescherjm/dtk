/* dtkDistributedCoreApplication.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/01/27 10:33:58
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkDistributedExport.h"

#include "dtkDistributedAbstractApplication.h"

#include <dtkCore/dtkCoreApplication.h>


class DTKDISTRIBUTED_EXPORT dtkDistributedCoreApplication: public QCoreApplication, public dtkDistributedAbstractApplication
{
public:
    dtkDistributedCoreApplication(int &argc, char **argv);

};

