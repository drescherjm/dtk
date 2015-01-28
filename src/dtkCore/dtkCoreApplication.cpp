/* @(#)dtkCoreApplication.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/01/26 12:26:59
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */



#include "dtkCoreApplication.h"

#include <dtkLog>

#include <QtCore>

class dtkCoreApplicationPrivate
{
public:
    QCommandLineParser   *parser;
    QSettings         *settings;
};

dtkCoreApplication::dtkCoreApplication(int &argc, char **argv) : QCoreApplication(argc,argv)
{
    d = new dtkCoreApplicationPrivate;
    d->parser   = new QCommandLineParser;
    d->parser->setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);

    d->settings = NULL;
}

dtkCoreApplication::~dtkCoreApplication(void)
{
    if (d->parser)
        delete d->parser;
    delete d;
    d = NULL;
}

QCommandLineParser *dtkCoreApplication::parser(void) const
{
    return d->parser;
}

QSettings *dtkCoreApplication::settings(void) const
{
    return d->settings;
}

void dtkCoreApplication::initialize(void)
{
    // unset QT_PLUGIN_PATH, otherwise, kde plugins can change the qmetatype ids
    qputenv("QT_PLUGIN_PATH", "1");
    qputenv("LC_ALL", "C");
    QLocale::setDefault(QLocale::c());

#if defined (Q_OS_UNIX) && !defined(Q_OS_MAC)
    // to avoid troubles with floats separators ('.' and not ',')
    setlocale(LC_NUMERIC, "C");
#endif

    d->parser->addHelpOption();
    d->parser->addVersionOption();

    bool opt;
    QCommandLineOption settingsOption("settings", "settings file", "filename");
    d->parser->addOption(settingsOption);

    QCommandLineOption verboseOption("verbose", QCoreApplication::translate("main", "verbose plugin initialization"));
    d->parser->addOption(verboseOption);

    QString verbosity = "info";
    QCommandLineOption loglevelOption("loglevel", "log level used by dtkLog (default is info)", "trace|debug|info|warn|error|fatal", verbosity);
    d->parser->addOption(loglevelOption);

    QCommandLineOption logfileOption("logfile", qPrintable(QString("log file used by dtkLog; default is: ").append(dtkLogPath(this))),"filename | console",dtkLogPath(this));
    d->parser->addOption(logfileOption);

    d->parser->process(*this);

    if(d->parser->isSet(settingsOption)) {
        d->settings = new QSettings(d->parser->value(settingsOption), QSettings::IniFormat);
    } else {
        d->settings = new QSettings(this->organizationName(), this->applicationName());
    }
    if (d->settings->contains("log_level")) {
        dtkLogger::instance().setLevel(d->settings->value("log_level").toString());
    } else {
        if (d->parser->isSet(loglevelOption)) {
            verbosity= d->parser->value(loglevelOption);
        }
        dtkLogger::instance().setLevel(verbosity);
    }
    if (d->parser->isSet(logfileOption)) {
        if (d->parser->value(logfileOption) == "console") {
            dtkLogger::instance().attachConsole();
        } else {
            dtkLogger::instance().attachFile(d->parser->value(logfileOption));
        }
    }
}
