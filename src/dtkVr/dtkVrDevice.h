/* dtkVrDevice.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 13:33:06 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 18 15:40:48 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRDEVICE_H
#define DTKVRDEVICE_H

#include "dtkVrExport.h"

#include <QtCore>

class dtkVrDevicePrivate;

class DTKVR_EXPORT dtkVrDevice : public QObject
{
    Q_OBJECT

public:
     dtkVrDevice(void);
    ~dtkVrDevice(void);

    virtual QString description(void) const = 0;

private:
    dtkVrDevicePrivate *d;
};

#endif
