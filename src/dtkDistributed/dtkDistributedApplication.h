/* dtkDistributedApplication.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/02/03 15:51:51
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
#include "dtkDistributedCoreApplication.h"

#include <QApplication>

class dtkDistributedPolicy;
class dtkDistributedCommunicator;
class dtkDistributedCoreApplicationPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedApplication: public QApplication, public dtkDistributedAbstractApplication
{
public:
    dtkDistributedApplication(int &argc, char **argv) ;

public:
    bool noGui(void);
};


