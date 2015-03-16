/* dtkDistributedApplication.cpp ---
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

#include "dtkDistributedApplication.h"

/*!
  \class dtkDistributedApplication
  \inmodule dtkDistributed
  \brief dtkDistributedApplication ...

*/

dtkDistributedApplication::dtkDistributedApplication(int &argc, char **argv) : QApplication(argc,argv), dtkDistributedAbstractApplication()
{
};

bool dtkDistributedApplication::noGui(void)
{
    return false;
};


