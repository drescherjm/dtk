/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 21 17:04:09 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Sep  6 11:38:49 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 35
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>

#include <dtkCore/dtkGlobal.h>

#include <dtkVr/dtkVrDeviceVrpn.h>
#include <dtkVr/dtkVrTrackerVrpn.h>

void trackerPositionHandler(float x, float y, float z)
{
    qDebug() << "tracker handler:" << x << y << z;
}

void devicePositionHandler(float x, float y, float z)
{
    qDebug() << "device handler:" << x << y << z;
}

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    if(dtkApplicationArgumentsContain(qApp, "--tracker")) {
        dtkVrTrackerVrpn *tracker = new dtkVrTrackerVrpn;
        tracker->registerPositionHandler1(trackerPositionHandler);
        tracker->startConnection(dtkApplicationArgumentsValue(qApp, "--tracker"));
        QObject::connect(qApp, SIGNAL(aboutToQuit()), tracker, SLOT(stopConnection()));
    }

    if(dtkApplicationArgumentsContain(qApp, "--device")) {
        dtkVrDeviceVrpn *device = new dtkVrDeviceVrpn;
        device->registerPositionHandler(devicePositionHandler);
        device->startConnection(dtkApplicationArgumentsValue(qApp, "--device"));
        QObject::connect(qApp, SIGNAL(aboutToQuit()), device, SLOT(stopConnection()));
    }

    int status = application.exec();
}
