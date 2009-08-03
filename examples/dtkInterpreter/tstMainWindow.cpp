/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 10 09:19:56 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr 17 13:54:28 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui>

#include "tstMainWindow.h"

#include <dtkGui/dtkTextEditorCompleter.h>
#include <dtkGui/dtkInterpreter.h>
#include <dtkGui/dtkInterpreterPreferencesWidget.h>

class tstMainWindowPrivate
{
public:
    QMenu *fileMenu;

    QAction *preferencesAction;

    dtkTextEditorCompleter *completer;

    dtkInterpreter *interpreter;

public:
    tstMainWindow *q;
};

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent)
{
    d = new tstMainWindowPrivate;

    d->interpreter = new dtkInterpreter(this);
    d->interpreter->readSettings();

    d->completer = new dtkTextEditorCompleterPath(d->interpreter);
    d->interpreter->setCompleter(d->completer);

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
