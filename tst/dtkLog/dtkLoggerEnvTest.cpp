/* dtkLoggerEnvTest.h --- 
 * 
 * Author: Julien Wintz
 * Created: Wed Feb 13 15:45:42 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Feb 13 16:23:21 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 75
 */

/* Change Log:
 * 
 */

#include "dtkLoggerEnvTest.h"

#include <dtkLog/dtkLogger.h>
#include <dtkLog/dtkLogger_p.h>

// ///////////////////////////////////////////////////////////////////
// Helper categories
// ///////////////////////////////////////////////////////////////////

DTK_LOG_CATEGORY(My_Category_A, "My.Category.A")
DTK_LOG_CATEGORY(My_Category_B, "My.Category.B")
DTK_LOG_CATEGORY(My_Category_C, "My.Category.C")

// ///////////////////////////////////////////////////////////////////
// Log rules file
// ///////////////////////////////////////////////////////////////////

#define LOGRULEFILE "./myLogRules.txt"

// ///////////////////////////////////////////////////////////////////
// Helper variables
// ///////////////////////////////////////////////////////////////////

QtMessageHandler env_oldMessageHandler;
bool env_logReceived = false;
QMutex env_threadmutex;

// ///////////////////////////////////////////////////////////////////
// Helper functions
// ///////////////////////////////////////////////////////////////////

QByteArray qMyMessageFormatStringEnv(QtMsgType /*type*/, const QMessageLogContext &/*context*/, const QString &str)
{
    QByteArray message;
    {
        message.append(qPrintable(str));
        message.append('\n');
    }

    return message;
}

static void myCustomMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QMutexLocker locker(&env_threadmutex);
    QString logmsg = qMyMessageFormatStringEnv(type, context, msg);
    if (logmsg.indexOf("My_Category") >= 0) {
        env_logReceived = true;
    }
    else
        env_oldMessageHandler(type, context, msg);
}

// ///////////////////////////////////////////////////////////////////
// Helper LogRules class
// ///////////////////////////////////////////////////////////////////

class LogRules
{
public:
    LogRules(void)
    {

    }

    void addKey(const QString &key, bool val){
        _values.insert(key, (val ? "true" : "false"));
        if(!_configitemEntryOrder.contains(key))
            _configitemEntryOrder.append(key);
    }

    QByteArray array(void)
    {
        QString ret;
        QTextStream out(&ret);
        for (int a = 0; a < _configitemEntryOrder.count(); a++) {
            out << _configitemEntryOrder[a] << " = " << _values.value(_configitemEntryOrder[a]) << endl;
        }
        out.flush();
        return ret.toLatin1();
    }

    void clear(void)
    {
        _values.clear();
        _configitemEntryOrder.clear();
    }

private:
    QMap<QString, QString> _values;
    QStringList _configitemEntryOrder;
};

// ///////////////////////////////////////////////////////////////////
// Helper LogThread class
// ///////////////////////////////////////////////////////////////////

class LogThreadEnv : public QThread
{
    Q_OBJECT

public:
    LogThreadEnv(void) {}

protected:
    void run(void);
};

void LogThreadEnv::run()
{
    dtkDebug(My_Category_A) << "My_Category_A";
    dtkDebug(My_Category_B) << "My_Category_B";
    dtkDebug(My_Category_C) << "My_Category_C";

    dtkWarning(My_Category_A) << "My_Category_A";
    dtkWarning(My_Category_B) << "My_Category_B";
    dtkWarning(My_Category_C) << "My_Category_C";

    dtkCritical(My_Category_A) << "My_Category_A";
    dtkCritical(My_Category_B) << "My_Category_B";
    dtkCritical(My_Category_C) << "My_Category_C";
}

// ///////////////////////////////////////////////////////////////////
// Helper variables
// ///////////////////////////////////////////////////////////////////

LogRules logRules;

// ///////////////////////////////////////////////////////////////////
// Helper Thread class
// ///////////////////////////////////////////////////////////////////

class WriteFileThread : public QThread
{
public:
    WriteFileThread(void) {}

protected:
    void run(void)
    {
        if (QFile::exists(LOGRULEFILE))
            QFile::remove(LOGRULEFILE);
        QFile file(LOGRULEFILE);
        if (file.open(QIODevice::WriteOnly))
            file.write(logRules.array());
    }
};

// ///////////////////////////////////////////////////////////////////
// Test case
// ///////////////////////////////////////////////////////////////////

void dtkLoggerEnvTestCase::initTestCase(void)
{
    env_oldMessageHandler = qInstallMessageHandler(myCustomMessageHandler);
    
    // Prepare for testcase log with NOT callin qSetLoggingRules & Co
    // Only the QT_LOGGING_CONFIG environment variable should activate
    // the logging qDebug & co are redefined to avoid creating the
    // dtkLogger private instance uncontrolled.
    QByteArray ba;
    ba.append(LOGRULEFILE);
    qputenv("QT_LOGGING_CONFIG", ba);
    
    // Create log rules
    logRules.addKey("My.Category.*", true);
    pFileWriter = new WriteFileThread();
    writeLogRuleFile();

    // Make sure the rule file exists otherwise QtLogger will not be active
    QTRY_VERIFY(QFile::exists(LOGRULEFILE));
}

void dtkLoggerEnvTestCase::createQtLoggerFromThread(void)
{
    env_logReceived = false;
    LogThreadEnv thread;
    
    // QtLogger private was created not in the main thread.
    thread.start();
    thread.wait();
    
    //Make sure that message handler was called => logger private instance is created
    QTRY_VERIFY(env_logReceived);
}

void dtkLoggerEnvTestCase::checkFileWatcherTrigger(void)
{
    //Now logger exist
    dtkLoggingPrivate *logger = dtkLogger();
    QTRY_VERIFY(logger->_configFileWatcher);
    
    //Check filewriter trigger
    QSignalSpy spy(logger, SIGNAL(configurationChanged()));
    logRules.addKey("My.Category.*", false);
    pFileWriter = new WriteFileThread();
    writeLogRuleFile();
    QTRY_VERIFY(spy.count() > 0);
    
    //Check filewriter trigger again
    spy.clear();
    logRules.addKey("My.Category.*", true);
    pFileWriter = new WriteFileThread();
    writeLogRuleFile();
    QTRY_VERIFY(spy.count() > 0);
}
 
void dtkLoggerEnvTestCase::cleanupTestCase(void)
{
    qInstallMessageHandler(env_oldMessageHandler);
    if (QFile::exists(LOGRULEFILE))
	QFile::remove(LOGRULEFILE);
    delete pFileWriter;
}

void dtkLoggerEnvTestCase::writeLogRuleFile(void)
{
    pFileWriter->start();
    pFileWriter->wait();
} 

#include "dtkLoggerEnvTest.moc"

DTKTEST_MAIN_NOGUI(dtkLoggerEnvTest, dtkLoggerEnvTestCase)

/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the test suite of the Qt Toolkit.
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
****************************************************************************/
