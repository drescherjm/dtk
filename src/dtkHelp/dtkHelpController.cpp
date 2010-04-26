/* dtkHelpController.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 16:02:30 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Apr 26 16:15:43 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 236
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkHelpController.h"

class dtkHelpControllerPrivate
{
public:
    QHelpEngine *engine;

    QMap<QString, QVariant> paths;
};

dtkHelpController *dtkHelpController::instance(void)
{
    if(!s_instance)
        s_instance = new dtkHelpController;

    return s_instance;
}

void dtkHelpController::initialize(void)
{
    this->readSettings();
}

void dtkHelpController::uninitialize(void)
{
    this->writeSettings();
}

void dtkHelpController::readSettings(void)
{
    QMap<QString, QVariant> paths;

    QSettings settings("inria", "dtk");
    settings.beginGroup("help");
    paths = settings.value("paths").toMap();
    settings.endGroup();

    foreach(QString key, paths.keys())
        if(d->engine->customFilters().contains(key))
            d->paths.insert(key, paths.value(key));

    if(paths.isEmpty() && QFile::exists("/usr/local/inria/doc/dtk.qhc"))
        d->paths.insert("fr.inria.dtk", "/usr/local/inria/doc/html/");
}

void dtkHelpController::writeSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("help");
    settings.setValue("paths", d->paths);
    settings.endGroup();
}

bool dtkHelpController::registerDocumentation(const QString& path)
{
    if(!QFile::exists(path)) {
        qDebug() << "Help collection file" << path << "does not exist";
        return false;
    }

    if (!d->engine->registerDocumentation(path)) {
        qDebug() << "Unable to register documentation" << path << d->engine->error();
        return false;
    }

    d->engine->setupData();

    d->paths.insert(d->engine->namespaceName(path),
                    d->engine->filterAttributes(d->engine->namespaceName(path)).first());

    return true;
}

bool dtkHelpController::unregisterDocumentation(const QString& namespaceName)
{
    if(!d->engine->unregisterDocumentation(namespaceName)) {
        qDebug() << "Unable to unregister documentation" << namespaceName << d->engine->error();
        return false;
    }

    d->engine->setupData();

    d->paths.remove(namespaceName);

    return true;
}

QHelpEngine *dtkHelpController::engine(void)
{
    return d->engine;
}

QUrl dtkHelpController::filter(const QUrl& url) const
{
    QString key;

    foreach(QString namespaceName, d->paths.keys())
        if(namespaceName.toLower() == url.host())
            key = namespaceName;

    if(url.scheme() == "qthelp")
        return QUrl(d->paths.value(key).toString() + url.toString().remove(QString("qthelp://" + url.host() + "/doc")));
    else
        return url;
}

QStringList dtkHelpController::registeredNamespaces(void) const
{
    return d->paths.keys();
}

dtkHelpController::dtkHelpController(void) : QObject(), d(new dtkHelpControllerPrivate)
{
#ifdef Q_WS_MAC
    QString doc = qApp->applicationDirPath() + "/../../../../doc/dtk.qhc";
#else
    QString doc = qApp->applicationDirPath() + "/../doc/dtk.qhc";
#endif

    if(!QFile::exists(doc))
        qDebug() << "dtk documentation not found. Run \"make doc\" to produce it.";

    d->engine = new QHelpEngine(doc, this);
    d->engine->setupData();

    if(!d->engine->namespaceName(doc).isEmpty())
        d->paths.insert(d->engine->namespaceName(doc),
                        d->engine->filterAttributes(d->engine->namespaceName(doc)).first());
}

dtkHelpController::~dtkHelpController(void)
{
    delete d;

    d = NULL;
}

dtkHelpController *dtkHelpController::s_instance = NULL;
