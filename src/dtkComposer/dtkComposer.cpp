/* dtkComposer.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:34:49 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  1 13:47:48 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 146
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposer.h"
#include "dtkComposer_p.h"
#include "dtkComposerFactory.h"
#include "dtkComposerMachine.h"
#include "dtkComposerReader.h"
#include "dtkComposerScene.h"
#include "dtkComposerStack.h"
#include "dtkComposerView.h"
#include "dtkComposerWriter.h"

#include <dtkCore/dtkGlobal.h>

#include <QtCore>
#include <QtGui>
#include <QtNetwork>

// /////////////////////////////////////////////////////////////////
// dtkComposerPrivate
// /////////////////////////////////////////////////////////////////

void dtkComposerPrivate::download(const QUrl& url)
{
    QTemporaryFile file; file.setAutoRemove(false);
    
    if (!file.open()) {
        qDebug() << DTK_PRETTY_FUNCTION << "Unable to file for saving";
        return;
    }
        
    this->dwnl_ok = 0;
    
    QHttp http;
    
    connect(&http, SIGNAL(requestFinished(int, bool)), this, SLOT(onRequestFinished(int, bool)));

    http.setHost(url.host(), url.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp, url.port() == -1 ? 0 : url.port());
        
    if (!url.userName().isEmpty())
        http.setUser(url.userName(), url.password());
        
    QByteArray path = QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/");
    
    if (path.isEmpty()) {
        qDebug() << DTK_PRETTY_FUNCTION << "Invalid path" << url.path();
        return;
    }
    
    this->dwnl_id = http.get(path, &file);
    
    while(!this->dwnl_ok)
        qApp->processEvents();

    file.close();

    QFileInfo info(file);
    
    this->tempName = info.absoluteFilePath();
}

void dtkComposerPrivate::onRequestFinished(int id, bool error)
{
    if(id == this->dwnl_id)
        this->dwnl_ok = 1;
}

// /////////////////////////////////////////////////////////////////
// dtkComposer
// /////////////////////////////////////////////////////////////////

dtkComposer::dtkComposer(QWidget *parent) : QWidget(parent), d(new dtkComposerPrivate)
{
    d->machine = new dtkComposerMachine;

    d->factory = new dtkComposerFactory;

    d->stack = new dtkComposerStack;

    d->scene = new dtkComposerScene;
    d->scene->setFactory(d->factory);
    d->scene->setMachine(d->machine);
    d->scene->setStack(d->stack);

    d->view = new dtkComposerView;
    d->view->setScene(d->scene);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->view);
}

dtkComposer::~dtkComposer(void)
{
    delete d->machine;
    delete d->factory;
    delete d->stack;
    delete d;
    
    d = NULL;
}

bool dtkComposer::open(const QUrl& url)
{
    d->download(url);

    bool status = false;

    if(!d->tempName.isEmpty())
        status = this->open(d->tempName);

    return status;
}

bool dtkComposer::open(QString file)
{
    if (!file.isEmpty()) {
        
        dtkComposerReader reader;
        reader.setScene(d->scene);
        reader.read(file);
        
        d->fileName = file;
    }

    return true;
}

bool dtkComposer::save(QString file, dtkComposerWriter::Type type)
{
    QString fName = d->fileName;

    if(!file.isEmpty())
        fName = file;

    dtkComposerWriter writer;
    writer.setScene(d->scene);
    writer.write(fName, type);

    const QFileInfo fi(fName);
    d->fileName = fi.absoluteFilePath();

    return true;
}

bool dtkComposer::insert(QString file)
{
    if (!file.isEmpty()) {
        
        dtkComposerReader reader;
        reader.setScene(d->scene);
        reader.read(file, true);
    }

    return true;
}

dtkComposerMachine *dtkComposer::machine(void)
{
    return d->machine;
}

dtkComposerFactory *dtkComposer::factory(void)
{
    return d->factory;
}

dtkComposerStack *dtkComposer::stack(void)
{
    return d->stack;
}
