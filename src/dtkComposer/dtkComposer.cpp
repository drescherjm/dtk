/* dtkComposer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Sep  4 10:14:39 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jul 27 11:48:02 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 346
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
#include "dtkComposerScene.h"
#include "dtkComposerView.h"

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
};

dtkComposer::dtkComposer(QWidget *parent) : QWidget(parent), d(new dtkComposerPrivate)
{
    d->scene = new dtkComposerScene(this);
    d->view = new dtkComposerView(this);
    d->view->setScene(d->scene);

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
