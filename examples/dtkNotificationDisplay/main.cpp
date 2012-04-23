/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr 20 21:18:43 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 23 15:30:00 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 57
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>

#include <dtkGui>

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
            dtkNotify(QString::number(this->count++), 10000);
            msleep(2000);
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

class tstMainWindow : public QMainWindow
{
public:
     tstMainWindow(QWidget *parent = 0);
    ~tstMainWindow(void);

private:
    dtkNotificationDisplay *display;
};

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->display = new dtkNotificationDisplay(this);

    QToolBar *mainToolBar = this->addToolBar(tr("Main"));
    mainToolBar->addWidget(new dtkSpacer(this));
    mainToolBar->addWidget(this->display);
    mainToolBar->addWidget(new dtkSpacer(this));

    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setWindowTitle("dtk notification example");
}

tstMainWindow::~tstMainWindow(void)
{
    
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    dtkNotificationDisplay *window = new dtkNotificationDisplay;

    // tstMainWindow *window = new tstMainWindow;
    window->show();
    window->raise();

    NotificationProducer producer;
    producer.start();

    int status = application.exec();

    producer.stop();
    producer.wait();

    delete window;

    return status;
}
