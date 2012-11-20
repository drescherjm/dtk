/* dtkComposerPath.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Nov 19 11:42:27 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Nov 20 12:24:21 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 174
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerPath.h"
#include "dtkComposerScene.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerPathPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerPathPrivate
{
public:
    void clear(void);

public:
    dtkComposerScene *scene;

public:
    QHBoxLayout *layout;
};

void dtkComposerPathPrivate::clear(void)
{   
    QLayoutItem *child;
    
    while ((child = layout->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerPath
// /////////////////////////////////////////////////////////////////

dtkComposerPath::dtkComposerPath(QWidget *parent) : QFrame(parent), d(new dtkComposerPathPrivate)
{
    d->scene = NULL;

    d->layout = new QHBoxLayout(this);
    d->layout->setContentsMargins(10, 0, 10, 0);
    d->layout->setAlignment(Qt::AlignLeft);
}

dtkComposerPath::~dtkComposerPath(void)
{
    delete d;

    d = NULL;
}

QSize dtkComposerPath::sizeHint(void) const
{
    return QSize(100, 22);
}

void dtkComposerPath::setScene(dtkComposerScene *scene)
{
    if(d->scene)
        disconnect(d->scene, SIGNAL(changed()), this, SLOT(update()));

    d->scene = scene;

    if(d->scene)
        connect(d->scene, SIGNAL(changed()), this, SLOT(update()));

    this->update();
}

void dtkComposerPath::update(void)
{
    d->clear();

    dtkComposerSceneNode *current = d->scene->current();

    while(current != d->scene->root()) {

        if (d->layout->count())
            d->layout->insertWidget(0, new QLabel(">", this));

        d->layout->insertWidget(0, new QLabel(current->title(), this));
        
        current = current->parent();
    }

    if (d->layout->count())
        d->layout->insertWidget(0, new QLabel(">", this));

    d->layout->insertWidget(0, new QLabel(current->title(), this));

    QFrame::update();
}
