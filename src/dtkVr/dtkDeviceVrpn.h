/* dtkDeviceVrpn.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jan 14 10:48:02 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Jan 14 10:52:31 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDEVICEVRPN_H
#define DTKDEVICEVRPN_H

#include "dtkAbstractDevice.h"
#include "dtkVrExport.h"

class dtkDeviceVrpnPrivate;

class dtkDeviceVrpn : public dtkAbstractDevice
{
    Q_OBJECT

public:
             dtkDeviceVrpn(      dtkAbstractObject *parent = 0);
             dtkDeviceVrpn(const dtkDeviceVrpn& data);
    virtual ~dtkDeviceVrpn(void);

private:
    dtkDeviceVrpnPrivate *d;
};

#endif
