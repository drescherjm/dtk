/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Oct 21 19:20:52 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Oct 21 19:20:56 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstMainWindow.h"
#include "tstWidget.h"

class tstMainWindowPrivate
{
public:
    tstWidget *widget;
};

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent), d(new tstMainWindowPrivate)
{
    d->widget = new tstWidget(this);

    this->setCentralWidget(d->widget);
}

tstMainWindow::~tstMainWindow(void)
{
    delete d;

    d = NULL;
}

void tstMainWindow::setTracker(QUrl tracker)
{
    d->widget->setTracker(tracker);
}
