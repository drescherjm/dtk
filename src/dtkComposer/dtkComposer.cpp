/* dtkComposer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Sep  4 10:14:39 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Aug 16 15:25:17 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 389
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposer.h"
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

class dtkComposerPrivate
{
public:
    dtkComposerScene *scene;
    dtkComposerView *view;

    QString fileName;
};

dtkComposer::dtkComposer(QWidget *parent) : QWidget(parent), d(new dtkComposerPrivate)
{
    d->scene = new dtkComposerScene(this);
    d->view = new dtkComposerView(this);
    d->view->setScene(d->scene);

    d->fileName = "untitled";

    connect(d->scene, SIGNAL(dataSelected(dtkAbstractData *)), this, SIGNAL(dataSelected(dtkAbstractData *)));
    connect(d->scene, SIGNAL(processSelected(dtkAbstractProcess *)), this, SIGNAL(processSelected(dtkAbstractProcess *)));
    connect(d->scene, SIGNAL(viewSelected(dtkAbstractView *)), this, SIGNAL(viewSelected(dtkAbstractView *)));

    connect(d->scene, SIGNAL(nodeAdded(dtkComposerNode *)), this, SIGNAL(nodeAdded(dtkComposerNode *)));
    connect(d->scene, SIGNAL(nodeRemoved(dtkComposerNode *)), this, SIGNAL(nodeRemoved(dtkComposerNode *)));

    connect(d->scene, SIGNAL(evaluationStarted()), this, SIGNAL(evaluationStarted()));
    connect(d->scene, SIGNAL(evaluationStopped()), this, SIGNAL(evaluationStopped()));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->view);

    emit titleChanged(d->fileName);
}

dtkComposer::~dtkComposer(void)
{
    delete d->scene;
    delete d->view;
    delete d;
    
    d = NULL;
}

void dtkComposer::setFactory(dtkComposerNodeFactory *factory)
{
    d->scene->setFactory(factory);
}

bool dtkComposer::isModified(void)
{
    return true;
}

QString dtkComposer::fileName(void)
{
    return d->fileName;
}

bool dtkComposer::open(QString fileName)
{
    if (!fileName.isEmpty()) {
        
        dtkComposerReader reader(d->scene);
        reader.read(fileName);

        QFileInfo info(fileName);

        emit titleChanged(info.baseName());
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

    emit titleChanged(fi.fileName());

    return true;
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
