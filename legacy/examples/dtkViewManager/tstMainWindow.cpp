/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:43:15 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 16 09:43:53 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstMainWindow.h"

#include <dtkGui/dtkViewManager.h>

class tstMainWindowPrivate
{
public:
    dtkViewManager *manager;
};

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent), d(new tstMainWindowPrivate)
{
    d->manager = new dtkViewManager(this);

    this->setCentralWidget(d->manager);
    this->setWindowTitle("dtk view manager example");
}

tstMainWindow::~tstMainWindow(void)
{
    delete d;

    d = NULL;
}
