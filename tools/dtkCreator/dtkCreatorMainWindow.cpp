/* dtkCreatorMainWindow.cpp ---
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:40:34 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 19:43:29 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 532
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCreatorMainWindow.h"

#include <dtkComposer/dtkComposer.h>

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
};

bool dtkCreatorMainWindowPrivate::maySave(void)
{

}

dtkCreatorMainWindow::dtkCreatorMainWindow(QWidget *parent) : QMainWindow(parent), d(new dtkCreatorMainWindowPrivate)
{
    d->composer = new dtkComposer;

    this->setCentralWidget(d->composer);
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
