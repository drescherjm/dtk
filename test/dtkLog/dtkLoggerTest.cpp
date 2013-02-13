/* dtkLoggerTest.cpp --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb 11 23:22:21 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Feb 13 16:06:29 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 100
 */

/* Change Log:
 * 
 */

#include "dtkLoggerTest.h"

#include <dtkLog/dtkLogger.h>
#include <dtkLog/dtkLogger_p.h>

// ///////////////////////////////////////////////////////////////////
// Define test log categories
// ///////////////////////////////////////////////////////////////////

DTK_LOG_CATEGORY(TST_LOG, "tst.log")
DTK_LOG_CATEGORY(TST_LOG1, "tst.log1")
DTK_LOG_CATEGORY(Inria_A_Project_com, "Inria.A.Project.fr")
DTK_LOG_CATEGORY(Inria_B_Project_com, "Inria.B.Project.fr")
DTK_LOG_CATEGORY(Inria_c_Project_com, "Inria.C.Project.fr")

// ///////////////////////////////////////////////////////////////////
// Helper variables
// ///////////////////////////////////////////////////////////////////

QtMessageHandler oldMessageHandler;
QString logMessage;
bool multithreadtest = false;
QStringList threadtest;
QMutex threadmutex;
bool usedefaultformat = false;

// ///////////////////////////////////////////////////////////////////
// Helper functions
// ///////////////////////////////////////////////////////////////////

QByteArray qMyMessageFormatString(QtMsgType type, const QMessageLogContext &context, const QString &str)
{
    QByteArray message;
    if(!usedefaultformat) {
        message.append(context.category);
        switch (type) {
        case QtDebugMsg:   message.append(".debug"); break;
        case QtWarningMsg: message.append(".warning"); break;
        case QtCriticalMsg:message.append(".critical"); break;
        case QtFatalMsg:   message.append(".fatal"); break;
        }
        message.append(": ");
        message.append(qPrintable(str));
        message.append('\n');
    } else {
        message.append(qPrintable(str));
        message.append('\n');
    }

    return message;
}

static void myCustomMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QMutexLocker locker(&threadmutex);
    logMessage = qMyMessageFormatString(type, context, msg);
    if (multithreadtest)
        threadtest.append(logMessage);
}

// ///////////////////////////////////////////////////////////////////
// Helper classes
// ///////////////////////////////////////////////////////////////////

class CfgFile
{
public:
    CfgFile(void)
    {
    
    }

    void addKey(const QString &key, bool val) {
        _values.insert(key, (val ? "true" : "false"));
        if(!_configitemEntryOrder.contains(key))
            _configitemEntryOrder.append(key);
    }
    
    void addKey(const QString &key, const QString &val){
        _values.insert(key, val);
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
// Helper variables
// ///////////////////////////////////////////////////////////////////

static CfgFile      cfg1;
static CfgFile      cfg2;
static CfgFile    *_cfgFile;
static CfgFile *_configFile;

// ///////////////////////////////////////////////////////////////////
// Helper classes
// ///////////////////////////////////////////////////////////////////

class LogThread : public QThread
{
    Q_OBJECT
    
public:
    LogThread(const QString &logtext, CfgFile *cfgFile) : _logtext(logtext)
    {
        _cfgFile = cfgFile;
    }
    
protected:
    void run(void)
    {
        for (int i = 0; i < 2000; i++) {
	    
            _cfgFile->addKey("Inria*", true);
            QByteArray arr = _cfgFile->array();
            dtkSetLoggingRules(arr);
            dtkDebug(Inria_A_Project_com) << "A " << _logtext << " :true";
            _cfgFile->addKey("Inria*", false);
            arr = _cfgFile->array();
            dtkSetLoggingRules(arr);
            dtkDebug(Inria_A_Project_com) << "A " << _logtext << " :false";
            
            _cfgFile->addKey("Inria*", true);
            arr = _cfgFile->array();
            dtkSetLoggingRules(arr);
            dtkDebug(Inria_c_Project_com) << "C " << _logtext << " :true";
            _cfgFile->addKey("Inria*", false);
            arr = _cfgFile->array();
            dtkSetLoggingRules(arr);
            dtkDebug(Inria_c_Project_com) << "C " << _logtext << " :false";
            
            _cfgFile->addKey("Inria*", true);
            arr = _cfgFile->array();
            dtkSetLoggingRules(arr);
            dtkDebug(Inria_B_Project_com) << "B " << _logtext << " :true";
            _cfgFile->addKey("Inria*", false);
            arr = _cfgFile->array();
            dtkSetLoggingRules(arr);
            dtkDebug(Inria_B_Project_com) << "B " << _logtext << " :false";
        }
    }
    
public:
    QString _logtext;
};

// ///////////////////////////////////////////////////////////////////
// Helper functions
// ///////////////////////////////////////////////////////////////////

inline QString cleanLogLine(QString& qstring)
{
    QString buf = qstring.replace("../", "");
    buf = buf.replace("qlog/", "");
    QString ret;
    for (int i = 0; i < buf.length(); i++) {
        if (buf[i] >= '!' && buf[i] <= 'z')
            ret += buf[i];
    }
    return ret;
}

// ///////////////////////////////////////////////////////////////////
// dtkLoggerTestCase
// ///////////////////////////////////////////////////////////////////

void dtkLoggerTestCase::initTestCase(void)
{
    qputenv("QT_MESSAGE_PATTERN", QString("%{category}: %{type},%{message}").toLatin1());

    oldMessageHandler = qInstallMessageHandler(myCustomMessageHandler);

    // Create dtkLog config file
    _configFile = new CfgFile();
}

void dtkLoggerTestCase::checkNoCategoryLogActive(void)
{
    // Check the Debug, Warning and critical without having category
    // active. should be active.

    QString buf;
    
    // Check default debug
    buf = QString::fromLatin1("default.debug: Check default Debug with no log active");
    qDebug() << "Check default Debug with no log active";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    
    // Check default warning
    buf = QString::fromLatin1("default.warning: Check default Warning with no log active");
    qWarning() << "Check default Warning with no log active";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    
    // Check default critical
    buf = QString::fromLatin1("default.critical: Check default Critical with no log active");
    qCritical() << "Check default Critical with no log active";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    
    // Check category debug
    logMessage = "should not change";
    buf = logMessage;
    dtkDebug(TST_LOG) << "Check category Debug with no log active";
    QCOMPARE(logMessage, buf);
    
    // Check default warning
    buf = QString::fromLatin1("tst.log.warning: Check category Warning with no log active");
    dtkWarning(TST_LOG) << "Check category Warning with no log active";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    
    // Check default critical
    buf = QString::fromLatin1("tst.log.critical: Check category Critical with no log active");
    dtkCritical(TST_LOG) << "Check category Critical with no log active";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
}

void dtkLoggerTestCase::writeCategoryLogs(void)
{
    usedefaultformat = false;

    // Activate TST_LOG category
    logMessage = "";
    _configFile->addKey("tst.log", true);
    dtkSetLoggingRules(_configFile->array());
    QString buf = QString::fromLatin1("tst.log.debug: Check for default messagePattern");
    dtkDebug(TST_LOG) << "Check for default messagePattern";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    
    // Activate TST_LOG category with default enabled function info
    _configFile->addKey("tst.log1", true);
    dtkSetLoggingRules(_configFile->array());
    dtkDebug(TST_LOG) << "1";
    buf = QString::fromLatin1("tst.log.debug: 1");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    
    // Wite out all different types
    dtkDebug(TST_LOG) << "DebugType";
    buf = QString::fromLatin1("tst.log.debug: DebugType");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    dtkWarning(TST_LOG) << "WarningType";
    buf = QString::fromLatin1("tst.log.warning: WarningType");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    dtkCritical(TST_LOG) << "CriticalType";
    buf = QString::fromLatin1("tst.log.critical: CriticalType");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
}

void dtkLoggerTestCase::checkLegacyLogs(void)
{
    logMessage = "";
    qDebug() << "DefaultDebug";
    QString buf = QString::fromLatin1("default.debug: DefaultDebug");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    
    // Default Debug off by default, warning and critical are on
    qWarning() << "DefaultWarning";
    buf = QString::fromLatin1("default.warning: DefaultWarning");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    qCritical() << "DefaultCritical";
    buf = QString::fromLatin1("default.critical: DefaultCritical");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    
    // Enable default debug
    _configFile->addKey("default.debug", true);
    dtkSetLoggingRules(_configFile->array());
    
    qDebug() << "DefaultDebug1";
    buf = QString::fromLatin1("default.debug: DefaultDebug1");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    qWarning() << "DefaultWarning1";
    buf = QString::fromLatin1("default.warning: DefaultWarning1");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    qCritical() << "DefaultCritical1";
    buf = QString::fromLatin1("default.critical: DefaultCritical1");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

    // Disable qWarning
    _configFile->addKey("default.warning", false);
    dtkSetLoggingRules(_configFile->array());

    qDebug() << "DefaultDebug2";
    buf = QString::fromLatin1("default.debug: DefaultDebug2");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    logMessage = "no change";
    qWarning() << "DefaultWarning2";
    buf = QString::fromLatin1("no change");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    qCritical() << "DefaultCritical2";
    buf = QString::fromLatin1("default.critical: DefaultCritical2");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

    // Disable qCritical
    _configFile->addKey("default.critical", false);
    _configFile->addKey("default.debug", false);
    dtkSetLoggingRules(_configFile->array());

    logMessage = "no change";
    qDebug() << "DefaultDebug3";
    buf = QString::fromLatin1("no change");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    qWarning() << "DefaultWarning3";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    qCritical() << "DefaultCritical3";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

    // Enable default logs
    _configFile->addKey("default.critical", true);
    _configFile->addKey("default.warning", true);
    _configFile->addKey("default.debug", true);
    dtkSetLoggingRules(_configFile->array());

    // Ensure all are on
    qDebug() << "DefaultDebug4";
    buf = QString::fromLatin1("default.debug: DefaultDebug4");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    qWarning() << "DefaultWarning4";
    buf = QString::fromLatin1("default.warning: DefaultWarning4");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    qCritical() << "DefaultCritical4";
    buf = QString::fromLatin1("default.critical: DefaultCritical4");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

    // Disable default log
    _configFile->addKey("default", false);
    dtkSetLoggingRules(_configFile->array());

    // Ensure all are off
    logMessage = "no change";
    buf = QString::fromLatin1("no change");
    qDebug() << "DefaultDebug5";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    qWarning() << "DefaultWarning5";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    qCritical() << "DefaultCritical5";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
}

void dtkLoggerTestCase::checkLegacyMessageLogger(void)
{
    usedefaultformat = true;

    //This should just not crash.
    QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO).debug() << "checkLegacyMessageLogger1";
    QCOMPARE(cleanLogLine(logMessage), QString("checkLegacyMessageLogger1"));
    QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO).warning() << "checkLegacyMessageLogger2";
    QCOMPARE(cleanLogLine(logMessage), QString("checkLegacyMessageLogger2"));
    QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO).critical() << "checkLegacyMessageLogger3";
    QCOMPARE(cleanLogLine(logMessage), QString("checkLegacyMessageLogger3"));
    usedefaultformat = false;
}

void dtkLoggerTestCase::checkFiltering(void)
{
    // Enable default logs
    _configFile->clear();
    _configFile->addKey("Inria.A.Project.fr", false);
    _configFile->addKey("Inria.B.Project.fr", false);
    _configFile->addKey("Inria.C.Project.fr", false);
    _configFile->addKey("MessagePattern", QString("%{category}: %{message}"));
    dtkSetLoggingRules(_configFile->array());

    logMessage = "no change";
    QString buf = QString::fromLatin1("no change");
    dtkDebug(Inria_A_Project_com) << "Inria.A.Project.fr 1";
    dtkDebug(Inria_B_Project_com) << "Inria.B.Project.fr 1";
    dtkDebug(Inria_c_Project_com) << "Inria.C.Project.fr 1";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

    _configFile->addKey("Inria.A.Project.fr", true);
    _configFile->addKey("Inria.B.Project.fr", true);
    _configFile->addKey("Inria.C.Project.fr", true);
    dtkSetLoggingRules(_configFile->array());

    dtkDebug(Inria_A_Project_com) << "Inria.A.Project.fr 2";
    buf = QString::fromLatin1("Inria.A.Project.fr.debug: Inria.A.Project.fr 2");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    dtkDebug(Inria_B_Project_com) << "Inria.B.Project.fr 2";
    buf = QString::fromLatin1("Inria.B.Project.fr.debug: Inria.B.Project.fr 2");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    dtkDebug(Inria_c_Project_com) << "Inria.C.Project.fr 2";
    buf = QString::fromLatin1("Inria.C.Project.fr.debug: Inria.C.Project.fr 2");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

    // Check right filter
    _configFile->addKey("Inria.A.Project.fr", false);
    _configFile->addKey("Inria.B.Project.fr", false);
    _configFile->addKey("Inria.C.Project.fr", false);
    _configFile->addKey("*Project.fr*", true);
    dtkSetLoggingRules(_configFile->array());

    dtkDebug(Inria_A_Project_com) << "Inria.A.Project.fr 3";
    buf = QString::fromLatin1("Inria.A.Project.fr.debug: Inria.A.Project.fr 3");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    dtkDebug(Inria_B_Project_com) << "Inria.B.Project.fr 3";
    buf = QString::fromLatin1("Inria.B.Project.fr.debug: Inria.B.Project.fr 3");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    dtkDebug(Inria_c_Project_com) << "Inria.C.Project.fr 3";
    buf = QString::fromLatin1("Inria.C.Project.fr.debug: Inria.C.Project.fr 3");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

    // Check left filter
    _configFile->addKey("*Project.fr*", false);
    _configFile->addKey("*Project.fr.debug", true);
    dtkSetLoggingRules(_configFile->array());

    dtkDebug(Inria_A_Project_com) << "Debug: Inria.A.Project.fr 4";
    buf = QString::fromLatin1("Inria.A.Project.fr.debug: Debug: Inria.A.Project.fr 4");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    logMessage = "no change";
    buf = QString::fromLatin1("no change");
    dtkWarning(Inria_B_Project_com) << "Warning: Inria.B.Project.fr 4";
    dtkCritical(Inria_c_Project_com) << "Critical: Inria.C.Project.fr 4";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

    // Check right filter
    _configFile->addKey("*Project.fr.debug", false);
    _configFile->addKey("Inria.*", true);
    dtkSetLoggingRules(_configFile->array());

    dtkDebug(Inria_A_Project_com) << "Debug: Inria.A.Project.fr 5";
    buf = QString::fromLatin1("Inria.A.Project.fr.debug: Debug: Inria.A.Project.fr 5");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    dtkWarning(Inria_B_Project_com) << "Warning: Inria.B.Project.fr 5";
    buf = QString::fromLatin1("Inria.B.Project.fr.warning: Warning: Inria.B.Project.fr 5");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    dtkCritical(Inria_c_Project_com) << "Critical: Inria.C.Project.fr 5";
    buf = QString::fromLatin1("Inria.C.Project.fr.critical: Critical: Inria.C.Project.fr 5");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

    // Check mid filter
    _configFile->addKey("Inria.*", false);
    dtkSetLoggingRules(_configFile->array());

    logMessage = "no change";
    buf = QString::fromLatin1("no change");
    dtkDebug(Inria_A_Project_com) << "Debug: Inria.A.Project.fr 6";
    dtkWarning(Inria_B_Project_com) << "Warning: Inria.B.Project.fr 6";
    dtkCritical(Inria_c_Project_com) << "Critical: Inria.C.Project.fr 6";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

    _configFile->addKey("*.Project.*", true);
    dtkSetLoggingRules(_configFile->array());

    dtkDebug(Inria_A_Project_com) << "Debug: Inria.A.Project.fr 7";
    buf = QString::fromLatin1("Inria.A.Project.fr.debug: Debug: Inria.A.Project.fr 7");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    dtkWarning(Inria_B_Project_com) << "Warning: Inria.B.Project.fr 7";
    buf = QString::fromLatin1("Inria.B.Project.fr.warning: Warning: Inria.B.Project.fr 7");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    dtkCritical(Inria_c_Project_com) << "Critical: Inria.C.Project.fr 7";
    buf = QString::fromLatin1("Inria.C.Project.fr.critical: Critical: Inria.C.Project.fr 7");
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
}

void dtkLoggerTestCase::checkLogWithCategoryObject(void)
{
    _configFile->clear();
    _configFile->addKey("LoggingCategoryObject", true);
    dtkLoggingCategory *pcategorybject = 0;
    dtkSetLoggingRules(_configFile->array());
    {
	dtkLoggingCategory mycategoryobject("LoggingCategoryObject");
	pcategorybject = &mycategoryobject;
	logMessage = "no change";

	QString buf = QString::fromLatin1("LoggingCategoryObject.debug: My Category Object");
	dtkDebug(mycategoryobject) << "My Category Object";
	QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

	buf = QString::fromLatin1("LoggingCategoryObject.warning: My Category Object");
	dtkWarning(mycategoryobject) << "My Category Object";
	QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

	buf = QString::fromLatin1("LoggingCategoryObject.critical: My Category Object");
	dtkCritical(mycategoryobject) << "My Category Object";
	QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

	dtkLoggingCategory mycategoryobject2("LoggingCategoryObject");
	buf = QString::fromLatin1("LoggingCategoryObject.debug: My Category Object");
	dtkDebug(mycategoryobject) << "My Category Object";
	QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

	buf = QString::fromLatin1("LoggingCategoryObject.warning: My Category Object");
	dtkWarning(mycategoryobject) << "My Category Object";
	QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

	buf = QString::fromLatin1("LoggingCategoryObject.critical: My Category Object");
	dtkCritical(mycategoryobject) << "My Category Object";
	QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
    }

    // Check if mycategoryobject still registered.
    dtkLoggingPrivate *logger = dtkLogger();

    QVERIFY(!logger->_registeredCategories.contains(pcategorybject));
}

void dtkLoggerTestCase::checkEmptyCategoryName(void)
{
    dtkLoggingCategory mycategoryobject("");

    logMessage = "no change";
    QString buf = QString::fromLatin1("no change");
    dtkDebug(mycategoryobject) << "My Category Object";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));

    dtkLoggingCategory mycategoryobject1(0);
    buf = QString::fromLatin1("no change");
    dtkDebug(mycategoryobject1) << "My Category Object";
    QCOMPARE(cleanLogLine(logMessage), cleanLogLine(buf));
}

void dtkLoggerTestCase::checkMultithreading(void)
{
    multithreadtest = true;

    // Init two cfgconf files fone for each thread
    cfg1.addKey("Inria*", true);
    cfg2.addKey("Inria*", true);
    QByteArray arr = cfg1.array();
    dtkSetLoggingRules(arr);

    LogThread thgread1(QString("from Thread 1"), &cfg1);
    LogThread thgread2(QString("from Thread 2"), &cfg2);

    // Writing out stuff from 2 different threads into the same LOG_CFG2
    thgread1.start();
    thgread2.start();
    thgread1.wait();
    thgread2.wait();

    // Check if each log line is complete
    QStringList compareagainst;
    QString buf;

    buf = QString::fromLatin1("Inria.A.Project.fr.debug: A  \"from Thread 1\"  :true");
    compareagainst.append(cleanLogLine(buf));
    buf = QString::fromLatin1("Inria.B.Project.fr.debug: B  \"from Thread 1\"  :true");
    compareagainst.append(cleanLogLine(buf));
    buf = QString::fromLatin1("Inria.C.Project.fr.debug: C  \"from Thread 1\"  :true");
    compareagainst.append(cleanLogLine(buf));

    buf = QString::fromLatin1("Inria.A.Project.fr.debug: A  \"from Thread 1\"  :false");
    compareagainst.append(cleanLogLine(buf));
    buf = QString::fromLatin1("Inria.B.Project.fr.debug: B  \"from Thread 1\"  :false");
    compareagainst.append(cleanLogLine(buf));
    buf = QString::fromLatin1("Inria.C.Project.fr.debug: C  \"from Thread 1\"  :false");
    compareagainst.append(cleanLogLine(buf));

    buf = QString::fromLatin1("Inria.A.Project.fr.debug: A  \"from Thread 2\"  :true");
    compareagainst.append(cleanLogLine(buf));
    buf = QString::fromLatin1("Inria.B.Project.fr.debug: B  \"from Thread 2\"  :true");
    compareagainst.append(cleanLogLine(buf));
    buf = QString::fromLatin1("Inria.C.Project.fr.debug: C  \"from Thread 2\"  :true");
    compareagainst.append(cleanLogLine(buf));

    buf = QString::fromLatin1("Inria.A.Project.fr.debug: A  \"from Thread 2\"  :false");
    compareagainst.append(cleanLogLine(buf));
    buf = QString::fromLatin1("Inria.B.Project.fr.debug: B  \"from Thread 2\"  :false");
    compareagainst.append(cleanLogLine(buf));
    buf = QString::fromLatin1("Inria.C.Project.fr.debug: C  \"from Thread 2\"  :false");
    compareagainst.append(cleanLogLine(buf));

    for (int i = 0; i < threadtest.count(); i++) {
	if (!compareagainst.contains(cleanLogLine(threadtest[i]))){
	    fprintf(stdout, "%s\r\n", threadtest[i].toLatin1().constData());
	    QVERIFY2(false, "Multithread log is not complete!");
	}
    }
}

void dtkLoggerTestCase::cleanupTestCase(void)
{
    delete _configFile;

    qInstallMessageHandler(oldMessageHandler);
}

#include "dtkLoggerTest.moc"

DTKTEST_MAIN_NOGUI(dtkLoggerTest, dtkLoggerTestCase)

/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the logger module of the Qt Toolkit.
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
