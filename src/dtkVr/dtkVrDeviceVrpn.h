/* dtkVrDeviceVrpn.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 13:43:20 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 18 20:21:49 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRDEVICEVRPN_H
#define DTKVRDEVICEVRPN_H

#include "dtkVrDevice.h"

class dtkVrDeviceVrpnPrivate;

class DTKVR_EXPORT dtkVrDeviceVrpn : public dtkVrDevice
{
    Q_OBJECT

public:
     dtkVrDeviceVrpn(void);
    ~dtkVrDeviceVrpn(void);

    typedef void (*dtkVrDeviceVrpnPositionHandler)(float x, float y, float z);
    typedef void (*dtkVrDeviceVrpnOrientationHandler)(float q0, float q1, float q2, float q3);

    void registerPositionHandler(dtkVrDeviceVrpn::dtkVrDeviceVrpnPositionHandler handler);
    void registerOrientationHandler(dtkVrDeviceVrpn::dtkVrDeviceVrpnOrientationHandler handler);

    enum Button {
        dtkVrDeviceVrpnButton1,
        dtkVrDeviceVrpnButton2,
        dtkVrDeviceVrpnButton3,
        dtkVrDeviceVrpnButton4,
        dtkVrDeviceVrpnButton5,
        dtkVrDeviceVrpnButton6,
        dtkVrDeviceVrpnButton7,
        dtkVrDeviceVrpnButton8,
        dtkVrDeviceVrpnButton9,
        dtkVrDeviceVrpnButtonUndefined
    };

    QString description(void) const;

signals:
    void buttonClicked(Button button);

public slots:
    void startConnection(const QUrl& server);
    void  stopConnection(void);

protected:
    void runPositionHandlers(float x, float y, float z);
    void runOrientationHandlers(float q0, float q1, float q2, float q3);

private:
    friend class dtkVrDeviceVrpnPrivate; dtkVrDeviceVrpnPrivate *d;
};

#endif
