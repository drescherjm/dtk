/* dtkAbstractDevice.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Jan 26 21:04:52 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan 26 21:10:20 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDEVICE_H
#define DTKABSTRACTDEVICE_H

#include <QtCore>

class dtkAbstractDevicePrivate;

class dtkAbstractDevice : public QObject
{
    Q_OBJECT

public:
             dtkAbstractDevice(void);
    virtual ~dtkAbstractDevice(void);

    virtual QString description(void) const = 0;

private:
    dtkAbstractDevicePrivate *d;
};

#endif
