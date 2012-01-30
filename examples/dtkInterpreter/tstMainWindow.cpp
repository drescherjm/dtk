/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 10 09:19:56 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 14:34:10 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 26
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui>

#include "tstMainWindow.h"

#include <dtkGui/dtkInterpreter.h>

class tstMainWindowPrivate
{
public:
    dtkInterpreter *interpreter;

public:
    tstMainWindow *q;
};

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent)
{
    d = new tstMainWindowPrivate;

    d->interpreter = new dtkInterpreter(this);
    d->interpreter->readSettings();

    d->q = this;

    this->setWindowTitle("dtk Gui Interpreter");
    this->setCentralWidget(d->interpreter);
}

tstMainWindow::~tstMainWindow(void)
{
    delete d->interpreter;
    delete d;
}

dtkInterpreter *tstMainWindow::interpreter(void)
{
    return d->interpreter;
}

void tstMainWindow::closeEvent(QCloseEvent *event)
{
    d->interpreter->writeSettings();
    event->accept();
}
