/* dtkUpdater.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jul 20 11:15:27 2009 (+0200)
 * Version: $Id$
 * Last-Updated: lun. févr.  3 14:47:49 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 23
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

    QByteArray path = QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/");
    if (path.isEmpty())
        path = "/";

    QNetworkRequest req(url);

    // FIXME: finish migration from QHTTP. Currently, it doesn't work.
    //    cfgId = http->get(req);

    // cfgId = http->get(path, cfgFile);
}

void dtkUpdaterPrivate::downl(const QUrl& url)
{
    if(!binFile->open(QFile::ReadWrite))
        qDebug() << "Unable to open binary file for saving";

    // FIXME: finish migration from QHTTP. Currently, it doesn't work.

//    binId = http->get(path, binFile);
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
    d->http = new QNetworkAccessManager;
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
