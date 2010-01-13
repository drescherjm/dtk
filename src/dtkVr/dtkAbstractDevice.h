/* dtkAbstractDevice.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Jan 13 14:10:22 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jan 13 15:16:31 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDEVICE_H
#define DTKABSTRACTDEVICE_H

#include <dtkCore/dtkAbstractObject.h>

#include "dtkVrExport.h"

class dtkAbstractDevicePrivate;

class DTKVR_EXPORT dtkAbstractDevice : public dtkAbstractObject
{
    Q_OBJECT

public:
             dtkAbstractDevice(      dtkAbstractObject *parent = 0);
             dtkAbstractDevice(const dtkAbstractDevice& data);
    virtual ~dtkAbstractDevice(void);

private:
    dtkAbstractDevicePrivate *d;
};

#endif
