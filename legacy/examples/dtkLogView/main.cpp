/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Mar  2 15:16:32 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  6 11:03:13 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 84
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkLog/dtkLog.h>
#include <dtkLog/dtkLogView.h>

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// Dummy thread
// /////////////////////////////////////////////////////////////////

class LogProducer : public QThread
{
public:
    LogProducer(void) {
        this->count = 1;
    }

    void run(void) {
        while(this->count) {
            dtkTrace() << count++;
            dtkDebug() << count;
            dtkInfo()  << count;
            dtkWarn()  << count;
            dtkError() << count;
            dtkFatal() << count;
            msleep(500);
        }
    }

    void stop(void) {
        this->count = 0;
    }

private:
    int count;
};

// /////////////////////////////////////////////////////////////////
// main
// /////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    QApplication application(argc, argv);
    application.setApplicationName("dtkLogView");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");

    dtkLogger::instance().setLevel(dtkLog::Trace);
    dtkLogger::instance().attachFile(dtkLogPath(&application));

    dtkLogView *view = new dtkLogView;
    view->setWindowTitle("dtk Log View");
    view->resize(680, 350);
    view->show();
    view->raise();

    LogProducer p1;
    p1.start();

    int status = application.exec();

    p1.stop();
    p1.wait();

    delete view;
    
    return status;
}
