/* dtkComposer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Sep  4 10:14:39 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Oct 18 13:32:01 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 486
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

// /////////////////////////////////////////////////////////////////
// dtkComposerPrivate
// /////////////////////////////////////////////////////////////////

void dtkComposerPrivate::download(const QUrl& url)
{
    qDebug() << DTK_PRETTY_FUNCTION << url;
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
    d->download(url);

    return true;
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
