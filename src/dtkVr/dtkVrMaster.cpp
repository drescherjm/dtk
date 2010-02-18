/* dtkVrMaster.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 10:03:10 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 18 11:19:05 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 43
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrMaster.h"

#include <QtCore>

class dtkVrMasterPrivate
{
public:
};

dtkVrMaster::dtkVrMaster(dtkDistributedCommunicator *communicator) : dtkVrProcess(communicator), d(new dtkVrMasterPrivate)
{

}

dtkVrMaster::~dtkVrMaster(void)
{
    delete d;
    
    d = NULL;
}

void dtkVrMaster::initialize(void)
{

}

void dtkVrMaster::uninitialize(void)
{
}

void dtkVrMaster::process(void)
{

}
