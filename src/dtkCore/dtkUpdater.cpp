/* dtkUpdater.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jul 20 11:15:27 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jan 27 17:13:13 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtNetwork>

#include "dtkGlobal.h"
#include "dtkUpdater_p.h"
#include "dtkUpdater.h"

// /////////////////////////////////////////////////////////////////
// dtkUpdaterPrivate
// /////////////////////////////////////////////////////////////////

void dtkUpdaterPrivate::onRequestFinished(int id, bool error)
{
    DTK_UNUSED(error);

    if (id == cfgId) {

        if(!cfgFile->openMode() == QIODevice::NotOpen)
            cfgFile->close();

        if (!cfgFile->open(QFile::ReadOnly | QFile::Text))
            qDebug() << "Unable to open stream for reading.";

        QXmlStreamReader reader(cfgFile);

        while (!reader.atEnd()) {
            reader.readNext();
            if (reader.isStartElement() && reader.attributes().hasAttribute("version") && reader.attributes().value("version").toString() > qApp->applicationVersion()) {
                reader.readNext();
                if(reader.isCharacters()) {
                    binUrl.setUrl(reader.text().toString());
                }
            }
        }

        if(!cfgFile->openMode() == QIODevice::NotOpen)
            cfgFile->close();

        if (reader.error())
            qDebug() << reader.error() << reader.errorString();

        if(binUrl.isEmpty()) {
            qDebug() << "You are up to date at version" << qApp->applicationVersion();
            return;
        } else {
            qDebug() << "Updates are available (you have " << qApp->applicationVersion() << "), would you like to download ?";
        }

        char c = getchar(); getchar();

        if(c == 'y')
            downl(binUrl);
    }

    else if (id == binId) {

        if(!binFile->openMode() == QIODevice::NotOpen)
            binFile->close();

        qDebug() << "Download completed, would you like to install ?";

        char c = getchar(); getchar();

        if(c == 'y')
            extract();
    }
}

void dtkUpdaterPrivate::check(const QUrl& url)
{   
    if(!cfgFile->open(QFile::ReadWrite))
        qDebug() << "Unable to open config file for parsing";

    http->setHost(url.host(), url.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp, url.port() == -1 ? 0 : url.port());

    if (!url.userName().isEmpty())
        http->setUser(url.userName(), url.password());

    QByteArray path = QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/");
    if (path.isEmpty())
        path = "/";

    cfgId = http->get(path, cfgFile);
}

void dtkUpdaterPrivate::downl(const QUrl& url)
{
    if(!binFile->open(QFile::ReadWrite))
        qDebug() << "Unable to open binary file for saving";

    http->setHost(url.host(), url.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp, url.port() == -1 ? 0 : url.port());

    if (!url.userName().isEmpty())
        http->setUser(url.userName(), url.password());

    QByteArray path = QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/");
    if (path.isEmpty())
        path = "/";

    binId = http->get(path, binFile);
}

void dtkUpdaterPrivate::extract(void)
{
    QProcess process;
#if defined (Q_OS_UNIX)
    QString input = "/tmp/bin";
    QString output = qApp->applicationDirPath();
# if defined (Q_OS_MAC)
    output += "/../../..";
# endif
    process.start("tar", QStringList() << "-xzf" << input << "-C" << output);
#else
    ;
#endif
    if(process.waitForFinished())
        qDebug() << "Updates have been installed successfully";
}

// /////////////////////////////////////////////////////////////////
// dtkUpdater
// /////////////////////////////////////////////////////////////////

dtkUpdater::dtkUpdater(const QUrl& cfgUrl)
{
    QFile::remove("/tmp/cfg");
    QFile::remove("/tmp/bin");

    d = new dtkUpdaterPrivate;
    d->http = new QHttp;
    d->cfgFile = new QFile("/tmp/cfg");
    d->binFile = new QFile("/tmp/bin");

    QObject::connect(d->http, SIGNAL(requestFinished(int, bool)), d, SLOT(onRequestFinished(int, bool)));

    d->check(cfgUrl);
}

dtkUpdater::~dtkUpdater(void)
{
    QFile::remove("/tmp/cfg");
    QFile::remove("/tmp/bin");
}

