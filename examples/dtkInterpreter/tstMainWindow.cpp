/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 10 09:19:56 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Aug  5 11:16:46 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 21
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
#include <dtkGui/dtkInterpreterPreferencesWidget.h>

class tstMainWindowPrivate
{
public:
    QMenu *fileMenu;

    QAction *preferencesAction;

    dtkInterpreter *interpreter;

public:
    tstMainWindow *q;
};

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent)
{
    d = new tstMainWindowPrivate;

    d->interpreter = new dtkInterpreter(this);
    d->interpreter->readSettings();

    d->preferencesAction = new QAction("Preferences", this);
    d->preferencesAction->setShortcut(Qt::ControlModifier + Qt::Key_Comma);
    connect(d->preferencesAction, SIGNAL(triggered()), this, SLOT(showPreferences()));

    d->fileMenu = this->menuBar()->addMenu("File");
    d->fileMenu->addAction(d->preferencesAction);

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

void tstMainWindow::showPreferences(void)
{
    dtkInterpreterPreferencesWidget *widget = d->interpreter->preferencesWidget(this);
    widget->setWindowFlags(Qt::Sheet);
    widget->show();
}

void tstMainWindow::closeEvent(QCloseEvent *event)
{
    d->interpreter->writeSettings();
    event->accept();
}
