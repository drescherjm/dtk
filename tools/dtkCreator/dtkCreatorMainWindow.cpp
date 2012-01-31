/* dtkCreatorMainWindow.cpp ---
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:40:34 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jan 31 18:12:56 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 577
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCreatorMainWindow.h"

#include <dtkComposer/dtkComposer.h>
#include <dtkComposer/dtkComposerFactoryView.h>
#include <dtkComposer/dtkComposerStackView.h>

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkCreatorMainWindowPrivate
// /////////////////////////////////////////////////////////////////

class dtkCreatorMainWindowPrivate
{
public:
    bool maySave(void);

public:
    dtkComposer *composer;
    dtkComposerFactoryView *nodes;
    dtkComposerStackView *stack;
};

bool dtkCreatorMainWindowPrivate::maySave(void)
{

}

dtkCreatorMainWindow::dtkCreatorMainWindow(QWidget *parent) : QMainWindow(parent), d(new dtkCreatorMainWindowPrivate)
{
    d->composer = new dtkComposer;

    d->stack = new dtkComposerStackView;
    d->stack->setStack(d->composer->stack());
    d->stack->setFixedWidth(300);

    d->nodes = new dtkComposerFactoryView;
    d->nodes->setFixedWidth(300);
    d->nodes->setFactory(d->composer->factory());

    QVBoxLayout *lateral = new QVBoxLayout;
    lateral->setContentsMargins(0, 0, 0, 0);
    lateral->setSpacing(0);
    lateral->addWidget(d->nodes);
    lateral->addWidget(d->stack);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addLayout(lateral);
    layout->addWidget(d->composer);

    QWidget *central = new QWidget(this);
    central->setLayout(layout);

    this->setCentralWidget(central);
    this->setWindowTitle("dtk Creator");

    this->readSettings();
}

dtkCreatorMainWindow::~dtkCreatorMainWindow(void)
{
    delete d;
}

void dtkCreatorMainWindow::readSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("creator");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(600, 400)).toSize();
    move(pos);
    resize(size);
    settings.endGroup();
}

void dtkCreatorMainWindow::writeSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("creator");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.endGroup();
}

void dtkCreatorMainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    this->writeSettings();
}
