/* dtkComposerControls.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Nov 20 16:21:59 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 21 14:00:22 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 83
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

public:
    QComboBox *selector;
    QListWidget *list;
};

dtkComposerControls::dtkComposerControls(QWidget *parent) : QFrame(parent), d(new dtkComposerControlsPrivate)
{
    d->scene = NULL;

// /////////////////////////////////////////////////////////////////

    d->selector = new QComboBox(this);
    d->selector->addItem(QIcon(":dtkComposer/pixmaps/dtk-composer-node-flag-blue.png"), "Blue flagged nodes");
    d->selector->addItem(QIcon(":dtkComposer/pixmaps/dtk-composer-node-flag-gray.png"), "Gray flagged nodes");
    d->selector->addItem(QIcon(":dtkComposer/pixmaps/dtk-composer-node-flag-green.png"), "Green flagged nodes");
    d->selector->addItem(QIcon(":dtkComposer/pixmaps/dtk-composer-node-flag-orange.png"), "Orange flagged nodes");
    d->selector->addItem(QIcon(":dtkComposer/pixmaps/dtk-composer-node-flag-pink.png"), "Pink flagged nodes");
    d->selector->addItem(QIcon(":dtkComposer/pixmaps/dtk-composer-node-flag-red.png"), "Red flagged nodes");
    d->selector->addItem(QIcon(":dtkComposer/pixmaps/dtk-composer-node-flag-yellow.png"), "Yellow flagged nodes");

// /////////////////////////////////////////////////////////////////

    d->list = new QListWidget(this);

// /////////////////////////////////////////////////////////////////

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(d->selector);
    layout->addWidget(d->list);

// /////////////////////////////////////////////////////////////////

    this->setFixedWidth(300);

// /////////////////////////////////////////////////////////////////

    connect(d->selector, SIGNAL(currentIndexChanged(int)), this, SLOT(setup(int)));
}

dtkComposerControls::~dtkComposerControls(void)
{
    delete d;

    d = NULL;
}

void dtkComposerControls::setScene(dtkComposerScene *scene)
{
    if(d->scene)
        disconnect(d->scene, SIGNAL(flagged()), this, SLOT(setup()));

    d->scene = scene;

    if(d->scene)
        connect(d->scene, SIGNAL(flagged()), this, SLOT(setup()));

    this->setup();
}

void dtkComposerControls::setup(void)
{
    qDebug() << Q_FUNC_INFO;
}

void dtkComposerControls::setup(int index)
{
    switch(index) {
    case 0:
        qDebug() << "Listing blue flag controls";
        break;
    case 1:
        qDebug() << "Listing gray flag controls";
        break;
    case 2:
        qDebug() << "Listing green flag controls";
        break;
    case 3:
        qDebug() << "Listing orange flag controls";
        break;
    case 4:
        qDebug() << "Listing pink flag controls";
        break;
    case 5:
        qDebug() << "Listing red flag controls";
        break;
    case 6:
        qDebug() << "Listing yellow flag controls";
        break;
    default:
        break;
    };
}
