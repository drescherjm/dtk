/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Mar  2 15:16:32 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Mar  2 19:09:13 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 61
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
// Helper function
// /////////////////////////////////////////////////////////////////

QString dtkLogPath(QCoreApplication *application);

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
            sleep(1);
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

    dtkLogger::instance().setLevel(dtkLog::Trace);

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

// /////////////////////////////////////////////////////////////////
// Helper function
// /////////////////////////////////////////////////////////////////

QString dtkLogPath(QCoreApplication *application)
{
    QString path = QDir(application->applicationDirPath()).filePath(QString("%1.log").arg(application->applicationName()));

    if (path.contains(QString("%1.app/Contents/MacOS/").arg(application->applicationName())))
        path.remove(QString("%1.app/Contents/MacOS/").arg(application->applicationName()));

    return path;
}
