/* dtkAbstractDevice.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Jan 13 14:11:56 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jan 13 15:15:46 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkAbstractDevice.h"

class dtkAbstractDevicePrivate
{
public:
};

dtkAbstractDevice::dtkAbstractDevice(dtkAbstractObject *parent) : dtkAbstractObject(parent), d(new dtkAbstractDevicePrivate)
{

}

dtkAbstractDevice::dtkAbstractDevice(const dtkAbstractDevice& data) : dtkAbstractObject(), d(new dtkAbstractDevicePrivate)
{

}

dtkAbstractDevice::~dtkAbstractDevice(void)
{
    delete d;

    d = NULL;
}
