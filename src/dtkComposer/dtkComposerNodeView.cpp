/* dtkComposerNodeView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr 24 23:29:24 2012 (+0200)
 * Version: $Id$
 * Last-Updated: ven. mai 11 16:18:49 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 149
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeVector3D.h"
#include "dtkComposerNodeQuaternion.h"
#include "dtkComposerNodeView.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkLog/dtkLog.h>

#include <dtkCore>

class dtkComposerNodeViewPrivate
{
public:
    dtkComposerTransmitterReceiver<QString> receiver_type;

public:
    dtkComposerTransmitterReceiver<bool> receiver_fullscreen;

public:
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_head_position;

public:
    dtkComposerTransmitterReceiver<dtkQuaternionReal> receiver_head_orientation;

public:
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_screen_upper_left;
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_screen_lower_left;
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_screen_lower_right;

public:
    dtkAbstractView *view;
};

dtkComposerNodeView::dtkComposerNodeView(void) : QObject(), dtkComposerNodeLeaf(), d(new dtkComposerNodeViewPrivate)
{
    d->view = NULL;

    this->appendReceiver(&(d->receiver_type));
    this->appendReceiver(&(d->receiver_fullscreen));
    this->appendReceiver(&(d->receiver_head_position));
    this->appendReceiver(&(d->receiver_head_orientation));
    this->appendReceiver(&(d->receiver_screen_upper_left));
    this->appendReceiver(&(d->receiver_screen_lower_left));
    this->appendReceiver(&(d->receiver_screen_lower_right));

    connect(this, SIGNAL(runned()), this, SLOT(onRun()));
}

dtkComposerNodeView::~dtkComposerNodeView(void)
{
    if (d->view)
        delete d->view;

    delete d;

    d = NULL;
}

void dtkComposerNodeView::run(void)
{
    emit runned();
    qApp->processEvents();
}

QString dtkComposerNodeView::type(void)
{
    return "view";
}

QString dtkComposerNodeView::titleHint(void)
{
    return "View";
}

QString dtkComposerNodeView::inputLabelHint(int port)
{
    if(port == 0)
        return "type";

    if(port == 1)
        return "fullscreen";

    if(port == 2)
        return "head position";

    if(port == 3)
        return "head orientation";

    if(port == 4)
        return "screen upper left";

    if(port == 5)
        return "screen lower left";

    if(port == 6)
        return "screen lower right";

    return dtkComposerNodeLeaf::inputLabelHint(port);
}

QString dtkComposerNodeView::outputLabelHint(int port)
{
    return dtkComposerNodeLeaf::outputLabelHint(port);
}

void dtkComposerNodeView::onRun(void)
{
    if (d->receiver_type.isEmpty()) {
        dtkWarn() << "no type speficied in view node!";
        return;
    }

    if(!d->view) {
        d->view = dtkAbstractViewFactory::instance()->create(d->receiver_type.data());

        if(!d->receiver_fullscreen.isEmpty() && d->receiver_fullscreen.data())
            d->view->widget()->showFullScreen();
        else
            d->view->widget()->show();
    }

    if (!d->view) {
        dtkWarn() << "no view, abort" <<  d->receiver_type.data();
        return;
    }

    if(!d->receiver_head_position.isEmpty())
        d->view->setHeadPosition(d->receiver_head_position.data());

    if(!d->receiver_head_orientation.isEmpty())
        d->view->setHeadOrientation(d->receiver_head_orientation.data());

    if(!d->receiver_screen_upper_left.isEmpty())
        d->view->setUpperLeft(d->receiver_screen_upper_left.data());

    if(!d->receiver_screen_lower_left.isEmpty())
        d->view->setLowerLeft(d->receiver_screen_lower_left.data());

    if(!d->receiver_screen_lower_right.isEmpty())
        d->view->setLowerRight(d->receiver_screen_lower_right.data());
}
