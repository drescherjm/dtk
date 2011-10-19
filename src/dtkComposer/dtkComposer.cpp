/* dtkComposer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Sep  4 10:14:39 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Oct 19 02:21:59 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 521
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposer.h"
#include "dtkComposer_p.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeFactory.h"
#include "dtkComposerReader.h"
#include "dtkComposerScene.h"
#include "dtkComposerView.h"
#include "dtkComposerWriter.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractView.h>

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
    d->scene = new dtkComposerScene;
    d->view = new dtkComposerView(this);
    d->view->setScene(d->scene);

    d->fileName = "untitled";

    connect(d->scene, SIGNAL(dataSelected(dtkAbstractData *)), this, SIGNAL(dataSelected(dtkAbstractData *)));
    connect(d->scene, SIGNAL(processSelected(dtkAbstractProcess *)), this, SIGNAL(processSelected(dtkAbstractProcess *)));
    connect(d->scene, SIGNAL(viewSelected(dtkAbstractView *)), this, SIGNAL(viewSelected(dtkAbstractView *)));

    connect(d->scene, SIGNAL(nodeAdded(dtkComposerNode *)), this, SIGNAL(nodeAdded(dtkComposerNode *)));
    connect(d->scene, SIGNAL(nodeRemoved(dtkComposerNode *)), this, SIGNAL(nodeRemoved(dtkComposerNode *)));
    connect(d->scene, SIGNAL(nodeSelected(dtkComposerNode *)), this, SIGNAL(nodeSelected(dtkComposerNode *)));
    connect(d->scene, SIGNAL(selectionCleared()), this, SIGNAL(selectionCleared()));
    connect(d->scene, SIGNAL(pathChanged(dtkComposerNode *)), this, SIGNAL(pathChanged(dtkComposerNode *)));

    connect(d->scene, SIGNAL(evaluationStarted()), this, SIGNAL(evaluationStarted()));
    connect(d->scene, SIGNAL(evaluationStopped()), this, SIGNAL(evaluationStopped()));

    connect(d->scene, SIGNAL(compositionChanged()), this, SIGNAL(compositionChanged()));

    connect(d->scene, SIGNAL(centerOn(const QPointF&)), d->view, SLOT(onCenterOn(const QPointF&)));
    connect(d->scene, SIGNAL(fitInView(const QRectF&)), d->view, SLOT(onFitInView(const QRectF&)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->view);

    emit titleChanged(d->fileName);
}

dtkComposer::~dtkComposer(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposer::setBackgroundColor(const QColor &color)
{
    d->view->setBackgroundBrush(color);
}

void dtkComposer::setFactory(dtkComposerNodeFactory *factory)
{
    d->scene->setFactory(factory);
}

void dtkComposer::setFileName(const QString& fileName)
{
    d->fileName = fileName;
}

bool dtkComposer::isModified(void)
{
    return d->scene->isModified();
}

QString dtkComposer::fileName(void)
{
    return d->fileName;
}

dtkComposerScene *dtkComposer::scene(void)
{
    return d->scene;
}

dtkComposerView *dtkComposer::view(void)
{
    return d->view;
}

bool dtkComposer::open(const QUrl& url)
{
    QString path;

    d->download(url);

    bool status = false;

    if(!d->tempName.isEmpty())
        status = this->open(d->tempName);

    qDebug() << d->tempName;

    // if(!d->tempName.isEmpty())
    //     QFile::remove(d->tempName);

    return status;
}

bool dtkComposer::open(QString fileName)
{
    if (!fileName.isEmpty()) {
        
        dtkComposerReader reader(d->scene);
        reader.read(fileName);

        d->scene->setModified(false);

        d->view->update();

        QFileInfo info(fileName);

        emit titleChanged(info.baseName());

        d->fileName = fileName;
    }

    return true;
}

bool dtkComposer::save(QString fileName)
{
    QString fName = d->fileName;

    if(!fileName.isEmpty())
        fName = fileName;

    dtkComposerWriter writer(d->scene);
    writer.write(fName);

    const QFileInfo fi(fName);
    d->fileName = fi.absoluteFilePath();

    d->scene->setModified(false);

    emit titleChanged(fi.fileName());

    return true;
}

bool dtkComposer::insert(QString fileName)
{
    if (!fileName.isEmpty()) {
        
        dtkComposerReader reader(d->scene);
        reader.read(fileName, true);

        d->scene->setModified(true);

        d->view->update();
    }

    return true;
}

void dtkComposer::group(QList<dtkComposerNode *> nodes)
{
    d->scene->createGroup(nodes);
}

void dtkComposer::ungroup(dtkComposerNode *node)
{
    d->scene->explodeGroup(node);
}

void dtkComposer::onDataSelected(dtkAbstractData *data)
{
    d->scene->clearSelection();

    // if(dtkComposerNode *node = data->node())
    //     node->setSelected(true);
}

void dtkComposer::onProcessSelected(dtkAbstractProcess *process)
{
    d->scene->clearSelection();

    // if(dtkComposerNode *node = process->node())
    //     node->setSelected(true);
}

void dtkComposer::onViewSelected(dtkAbstractView *view)
{
    d->scene->clearSelection();

    // if(dtkComposerNode *node = view->node())
    //     node->setSelected(true);
}

void dtkComposer::startEvaluation(void)
{
    d->scene->startEvaluation();
}

void dtkComposer::stopEvaluation(void)
{
    d->scene->stopEvaluation();
}

void dtkComposer::copy(void)
{
    d->scene->copy();
}

void dtkComposer::paste(void)
{
    d->scene->paste();
}
