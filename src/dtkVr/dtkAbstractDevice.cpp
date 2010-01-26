/* dtkAbstractDevice.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Jan 26 21:06:27 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan 26 21:12:47 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
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

dtkAbstractDevice::dtkAbstractDevice(void) : QObject(), d(new dtkAbstractDevicePrivate)
{

}

dtkAbstractDevice::~dtkAbstractDevice(void)
{
    delete d;

    d = NULL;
}
