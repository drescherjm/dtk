/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 15:23:18 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar  1 23:14:39 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 225
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkLog/dtkLog.h>

#include <QtCore>
#include <QtDebug>

// /////////////////////////////////////////////////////////////////
// QVariant compliant custom class
// /////////////////////////////////////////////////////////////////

class Pixel
{
public:
     Pixel(void);
     Pixel(int x, int y);
     Pixel(const Pixel& other);
    ~Pixel(void);

private:
    friend QDebug operator<<(QDebug dbg, const Pixel &pixel);

private:
    int m_x;
    int m_y;
};

Pixel::Pixel(void)
{
    this->m_x = 0;
    this->m_y = 0;
}

Pixel::Pixel(int x, int y)
{
    this->m_x = x;
    this->m_y = y;
}

Pixel::Pixel(const Pixel& other)
{
    this->m_x = other.m_x;
    this->m_y = other.m_y;
}

Pixel::~Pixel(void)
{

}

QDebug operator<<(QDebug dbg, const Pixel &pixel)
{
    dbg.nospace() << "Pixel(" << pixel.m_x << ", " << pixel.m_y << ")";

    return dbg.space();
}

Q_DECLARE_METATYPE(Pixel);

// /////////////////////////////////////////////////////////////////
// Helper function
// /////////////////////////////////////////////////////////////////

QString dtkLogPath(QCoreApplication *application);

// /////////////////////////////////////////////////////////////////
// main
// /////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);
    application.setApplicationName(argv[0]);

    qRegisterMetaType<Pixel>();

    dtkLogger::instance().setLevel(dtkLog::Trace);
    dtkLogger::instance().attachConsole();
    dtkLogger::instance().attachFile(dtkLogPath(&application));

    // /////////////////////////////////////////////////////////////////

      qDebug() << "Overview of logging levels:";
    dtkTrace() << "More detailed information.";
    dtkDebug() << "Detailed information on the flow through the system.";
     dtkInfo() << "Interesting runtime events (startup/shutdown).";
     dtkWarn() << "Runtime situations that are undesirable or unexpected, but not necessarily wrong.";
    dtkError() << "Other runtime errors or unexpected conditions.";
    dtkFatal() << "Severe errors that cause premature termination.";
      qDebug() << "";

    // /////////////////////////////////////////////////////////////////

    dtkLogger::instance().setLevel(dtkLog::Info);

     qDebug() << "Level management (current Level is dtkLog::Info):";
    dtkTrace() << "This message is logged as TRACE <  INFO";
    dtkDebug() << "This message is logged as DEBUG <  INFO";
     dtkInfo() << "This message is logged as  INFO == INFO";
     dtkWarn() << "This message is logged as  WARN >= INFO";
    dtkError() << "This message is logged as ERROR >= INFO";
    dtkFatal() << "This message is logged as FATAL >= INFO";
      qDebug() << "";

    dtkLogger::instance().setLevel(dtkLog::Trace);

    // /////////////////////////////////////////////////////////////////

    dtkLogger::instance().detachFile(dtkLogPath(&application));

      qDebug() << "Destination management:";
    dtkTrace() << "This message will no longer be logged to the file";
    dtkDebug() << "This message will no longer be logged to the file";

    dtkLogger::instance().attachFile(dtkLogPath(&application));

    dtkDebug() << "This message will be logged to the file";
      qDebug() << "";

    // /////////////////////////////////////////////////////////////////

    QList<int> list;
    list << 1;
    list << 2 << 3;

    QHash<int, QString> hash;
    hash.insert(1, "one");
    hash.insert(2, "two");
    hash.insert(3, "three");

    Pixel p(100, 250);

    QVariant variant; variant.setValue(p);

      qDebug() << "Handled types:";
    dtkTrace() << "Primitive types -" << true << 1 << 2.2;
    dtkDebug() << "Qt types -" << QString("String") << QChar('x') << QRect(0, 10, 50, 40);
    dtkError() << "Qt containers -" << list << hash;
    dtkFatal() << "Custom types -" << p << variant;
      qDebug() << "";

    int status = 0;

    dtkInfo() << "Program exited with return code" << status;

    return status;
}

// /////////////////////////////////////////////////////////////////
// Helper function
// /////////////////////////////////////////////////////////////////

QString dtkLogPath(QCoreApplication *application)
{
    return QDir(application->applicationDirPath()).filePath(QString("%1.log").arg(application->applicationName()));
}
