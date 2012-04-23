/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr 20 21:18:43 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Sat Apr 21 20:11:46 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 23
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>

#include <dtkNotification/dtkNotification.h>
#include <dtkNotification/dtkNotificationDisplay.h>

// /////////////////////////////////////////////////////////////////
// Notification producer
// /////////////////////////////////////////////////////////////////

class NotificationProducer : public QThread
{
public:
    NotificationProducer(void) {
        this->count = 1;
    }

    void run(void) {
        while(this->count) {
            dtkNotify(QString::number(this->count++), 500);
            msleep(1000);
        }
    }

    void stop(void) {
        this->count = 0;
    }

private:
    int count;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    dtkNotificationDisplay *display = new dtkNotificationDisplay;
    display->setAutoFillBackground(false);
    display->setWindowFlags(Qt::FramelessWindowHint);
    display->show();
    display->raise();

    NotificationProducer producer;
    producer.start();

    int status = application.exec();

    producer.stop();
    producer.wait();

    delete display;

    return status;
}
