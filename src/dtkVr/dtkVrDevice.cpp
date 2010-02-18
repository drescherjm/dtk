/* dtkVrDevice.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 13:41:01 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 18 13:43:05 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrDevice.h"

class dtkVrDevicePrivate
{
public:
};

dtkVrDevice::dtkVrDevice(void) : QObject(), d(new dtkVrDevicePrivate)
{

}

dtkVrDevice::~dtkVrDevice(void)
{
    delete d;

    d = NULL;
}
