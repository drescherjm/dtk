/* dtkComposerControls.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Nov 20 16:21:59 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Nov 20 17:13:33 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerControls.h"
#include "dtkComposerScene.h"

class dtkComposerControlsPrivate
{
public:
    dtkComposerScene *scene;
};

dtkComposerControls::dtkComposerControls(QWidget *parent) : QFrame(parent), d(new dtkComposerControlsPrivate)
{
    d->scene = NULL;

    this->setFixedWidth(300);
}

dtkComposerControls::~dtkComposerControls(void)
{
    delete d;

    d = NULL;
}

void dtkComposerControls::setScene(dtkComposerScene *scene)
{
    if(d->scene)
        disconnect(d->scene, SIGNAL(flagged()), this, SLOT(update()));

    d->scene = scene;

    if(d->scene)
        connect(d->scene, SIGNAL(flagged()), this, SLOT(update()));
}

void dtkComposerControls::update(void)
{
    qDebug() << Q_FUNC_INFO;
}
