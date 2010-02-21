/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 21 17:04:09 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb 21 17:52:17 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>

#include <dtkVr/dtkVrDeviceVrpn.h>
#include <dtkVr/dtkVrTrackerVrpn.h>

void trackerPositionHandler1(float x, float y, float z)
{
    qDebug() << "tracker handler 1:" << x << y << z;
}

void devicePositionHandler1(float x, float y, float z)
{
    qDebug() << "device handler 1:" << x << y << z;
}

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    dtkVrTrackerVrpn *tracker = new dtkVrTrackerVrpn;
    tracker->registerPositionHandler1(trackerPositionHandler1);
    tracker->startConnection(QUrl("DTrack@is-sound"));
    
    int status = application.exec();

    tracker->stopConnection();
}
