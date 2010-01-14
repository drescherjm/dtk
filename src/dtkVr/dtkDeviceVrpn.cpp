/* dtkDeviceVrpn.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jan 14 10:50:57 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Jan 14 11:21:58 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDeviceVrpn.h"

class dtkDeviceVrpnPrivate
{
public:
};

dtkDeviceVrpn::dtkDeviceVrpn(dtkAbstractObject *parent) : dtkAbstractDevice(parent), d(new dtkDeviceVrpnPrivate)
{

}

dtkDeviceVrpn::dtkDeviceVrpn(const dtkDeviceVrpn& data) : dtkAbstractDevice(), d(new dtkDeviceVrpnPrivate)
{

}

dtkDeviceVrpn::~dtkDeviceVrpn(void)
{
    delete d;

    d = NULL;
}
