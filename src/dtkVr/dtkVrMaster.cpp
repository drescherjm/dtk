/* dtkVrMaster.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 10:03:10 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon May  9 14:48:34 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 221
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrMaster.h"
#include "dtkVrDeviceVrpn.h"
#include "dtkVrTrackerVrpn.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkVec3.h>
#include <dtkCore/dtkQuat.h>

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkVrMasterPrivate
// /////////////////////////////////////////////////////////////////

class dtkVrMasterPrivate
{
public:
    static dtkVrMasterPrivate *self;

    dtkVrMaster *q;
};

dtkVrMasterPrivate *dtkVrMasterPrivate::self = NULL;

// /////////////////////////////////////////////////////////////////
// dtkVrMaster
// /////////////////////////////////////////////////////////////////

dtkVrMaster::dtkVrMaster(dtkDistributedCommunicator *communicator) : dtkVrProcess(communicator), d(new dtkVrMasterPrivate)
{
    d->q = this;
    d->self = d;
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
