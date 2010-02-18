/* dtkVrMaster.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 10:03:10 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 16 22:35:32 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 42
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

dtkVrMaster::dtkVrMaster(void) : dtkVrProcess(), d(new dtkVrMasterPrivate)
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
