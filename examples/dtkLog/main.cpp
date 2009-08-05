/* main.cpp --- 
 * 
 * Author: Jean-Christophe Lombardo
 * Copyright (C) 2009 - Jean-Christophe Lombardo, Inria
 * Created: Fri May 15 13:48:29 2009
 * Version: $Id$
 * Last-Updated: Wed Aug  5 10:57:25 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 37
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkLog.h>

#include <dtkGui/dtkTextEditor.h>

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// log messages handlers
// /////////////////////////////////////////////////////////////////

void   toFile(dtkLog::Level level, const QString& msg);
void toWidget(dtkLog::Level level, const QString& msg);

// /////////////////////////////////////////////////////////////////
// Dummy thread classes to test thread safety
// /////////////////////////////////////////////////////////////////

class Thread : public QThread
{
public:
    Thread(void) : m_idx(++s_idx) {};

    void run(void) {
        QString name("Thread "); name += QString::number(m_idx);

        for (int i = 0 ; i < 10 ; ++i) {

            dtkLog::output(name) << name << " writing on (" << name << ") output log - #" << i;
            dtkLog::output()     << name << " writing on default output log - #" << i;
            
            dtkLog::error(name)  << name << " writing on (" << name << ") error log - #" << i;
            dtkLog::error()      << name << " writing on default error log - #" << i;
            
            usleep(100);
        }
    }

private:
           int m_idx;
    static int s_idx;
};

int Thread::s_idx = 0;

// /////////////////////////////////////////////////////////////////
// Log handler example - redirection to file
// /////////////////////////////////////////////////////////////////

void toFile(dtkLog::Level level, const QString& msg) {

    QTemporaryFile file("dtk.log"); file.setAutoRemove(false);

    // if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    //     return;

    QTextStream out(&file); out << msg << "\n";
    
    file.close();
}

// /////////////////////////////////////////////////////////////////
// Log handler example - redirection to aware widget
// /////////////////////////////////////////////////////////////////

dtkTextEditor *widget = 0;

void toWidget(dtkLog::Level level, const QString& msg) {
    QCoreApplication::postEvent(widget, new dtkLogEvent(level, msg));
}

// /////////////////////////////////////////////////////////////////
// dtkLog example
// /////////////////////////////////////////////////////////////////

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    widget = new dtkTextEditor;
    widget->show();

    qDebug() << "Setting up   file handler - see /tmp/dtk.log on unix and mac, %TEMP%/dtk.log on windows";
    qDebug() << "Setting up widget handler - see text editor";

    dtkLog::registerHandler(toFile);
    dtkLog::registerHandler(toWidget);

    std::cerr << "cerr is redirected into default dtkLog" << 1 << ", " << 1.0 << std::endl;
    std::cout << "cout is redirected into default dtkLog" << 1 << ", " << 1.0 << std::endl;
    std::clog << "clog is redirected into default dtkLog" << 1 << ", " << 1.0 << std::endl;

    dtkLog::output() << "multiple type can be logged out " << 1 << ", " << 1.0;
    dtkLog::error () << "multiple type can be logged out " << 1 << ", " << 1.0;

    dtkLog::output()   << "This is the   output channel - for default source -";
    dtkLog::error()    << "This is the    error channel - for default source -";
    dtkLog::debug()    << "This is the    debug channel - for default source -";
    dtkLog::warning()  << "This is the  warning channel - for default source -";
    dtkLog::critical() << "This is the critical channel - for default source -";
    dtkLog::fatal()    << "This is the    fatal channel - for default source -";
        
    Thread t[20];
    for (unsigned int i = 0; i < 5;   ++i) t[i].start();
    for (unsigned int i = 0; i < 5;   ++i) t[i].wait();
    for (unsigned int i = 0; i < 500; ++i) app.processEvents();

    dtkLog::warning()  << "Disabling standard redirections";
    dtkLog::disableRedirection();
    std::cerr << "cerr is no more redirected into default dtkLog" << std::endl;
    std::cout << "cout is no more redirected into default dtkLog" << std::endl;
    std::clog << "clog is no more redirected into default dtkLog" << std::endl;

    return app.exec();
}

// -*- tab-width: 4; indent-tabs-mode: nil c-basic-offset: 4 -*-
// vim:cindent:ts=4:sw=4:et:tw=80:sta:
