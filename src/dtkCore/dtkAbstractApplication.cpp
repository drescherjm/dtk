/* dtkAbstractApplication.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/02/04 12:03:44
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkAbstractApplication.h"

class dtkAbstractApplicationPrivate
{
public:
    QSettings *settings;
    QCommandLineParser parser;

};

dtkAbstractApplication::dtkAbstractApplication(void)
{
    d = new dtkAbstractApplicationPrivate;
    d->settings = NULL;
    d->parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);

}

dtkAbstractApplication::~dtkAbstractApplication(void)
{
    if (d->settings)
        delete d->settings;

    delete d;
    d = NULL;
}

QSettings *dtkAbstractApplication::settings(void)
{
    return d->settings;
}

bool dtkAbstractApplication::noGui(void) {
    return true;
}

QCommandLineParser *dtkAbstractApplication::parser(void)
{
    return &(d->parser);
}

void dtkAbstractApplication::setApplicationName(const QString& name)
{
    qApp->setApplicationName(name);
}

QString dtkAbstractApplication::applicationName(void)
{
    return qApp->applicationName();
}

void dtkAbstractApplication::setOrganizationName(const QString& name)
{
    qApp->setOrganizationName(name);
}

void dtkAbstractApplication::setOrganizationDomain(const QString& name)
{
    qApp->setOrganizationDomain(name);
}

void dtkAbstractApplication::setApplicationVersion(const QString& version)
{
    qApp->setApplicationVersion(version);
}

void dtkAbstractApplication::initialize(void)
{
    // unset QT_PLUGIN_PATH, otherwise, kde plugins can change the qmetatype ids
    qputenv("QT_PLUGIN_PATH", "1");
    qputenv("LC_ALL", "C");
    QLocale::setDefault(QLocale::c());

#if defined (Q_OS_UNIX) && !defined(Q_OS_MAC)
    // to avoid troubles with floats separators ('.' and not ',')
    setlocale(LC_NUMERIC, "C");
#endif

    d->parser.addHelpOption();
    d->parser.addVersionOption();

    bool opt;
    QCommandLineOption settingsOption("settings", "settings file", "filename");
    d->parser.addOption(settingsOption);

    QCommandLineOption verboseOption("verbose", QCoreApplication::translate("main", "verbose plugin initialization"));
    d->parser.addOption(verboseOption);

    QCommandLineOption nonguiOption(QStringList() << "nw" << "no-window", QCoreApplication::translate("main", "non GUI application (no window)"));
    d->parser.addOption(nonguiOption);

    QString verbosity = "info";
    QCommandLineOption loglevelOption("loglevel", "log level used by dtkLog (default is info)", "trace|debug|info|warn|error|fatal", verbosity);
    d->parser.addOption(loglevelOption);

    QCoreApplication *q = dynamic_cast<QCoreApplication *>(this);
    QCommandLineOption logfileOption("logfile", qPrintable(QString("log file used by dtkLog; default is: ").append(dtkLogPath(q))),"filename | console",dtkLogPath(q));
    d->parser.addOption(logfileOption);

    d->parser.process(*q);

    if(d->parser.isSet(settingsOption)) {
        d->settings = new QSettings(d->parser.value(settingsOption), QSettings::IniFormat);
    } else {
        d->settings = new QSettings(q->organizationName(), q->applicationName());
    }
    if (d->settings->contains("log_level")) {
        dtkLogger::instance().setLevel(d->settings->value("log_level").toString());
    } else {
        if (d->parser.isSet(loglevelOption)) {
            verbosity= d->parser.value(loglevelOption);
        }
        dtkLogger::instance().setLevel(verbosity);
    }
    if (d->parser.isSet(logfileOption)) {
        if (d->parser.value(logfileOption) == "console") {
            dtkLogger::instance().attachConsole();
        } else {
            dtkLogger::instance().attachFile(d->parser.value(logfileOption));
        }
    }
}

