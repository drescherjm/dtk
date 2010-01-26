/* dtkDeviceTdx.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Jan 24 21:28:47 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan 26 21:09:26 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDEVICETDX_H
#define DTKDEVICETDX_H

#include "dtkAbstractDevice.h"

class dtkDeviceTdxPrivate;

class dtkDeviceTdx : public dtkAbstractDevice
{
    Q_OBJECT

public:
     dtkDeviceTdx(void);
    ~dtkDeviceTdx(void);

    typedef void (*dtkDeviceTdxHandler)(float tx, float ty, float tz, float rx, float ry, float rz);

    void registerHandler(dtkDeviceTdx::dtkDeviceTdxHandler handler);

    enum dtkDeviceTdxButton {
        dtkDeviceTdxButtonOne,
        dtkDeviceTdxButtonTwo
    };

    QString description(void) const;

signals:
    void buttonPressed(dtkDeviceTdx::dtkDeviceTdxButton);
    void buttonReleased(dtkDeviceTdx::dtkDeviceTdxButton);

public slots:
    void startConnection(void);
    void  stopConnection(void);

protected:
    QList<dtkDeviceTdx::dtkDeviceTdxHandler> handlers;

    void runHandlers(float tx, float ty, float tz, float rx, float ry, float rz);

private:
    friend class dtkDeviceTdxPrivate; dtkDeviceTdxPrivate *d;
};

#endif
