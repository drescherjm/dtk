/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 16:12:47 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 30 13:57:45 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 36
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui>

#include "tstMainWindow.h"
#include "tstInspectorDistributed.h"

#include <dtkGui/dtkInspector.h>
#include <dtkGui/dtkSpacer.h>

#include <dtkDistributed/dtkDistributedController.h>

// /////////////////////////////////////////////////////////////////
// tstMainWindowPrivate
// /////////////////////////////////////////////////////////////////

class tstMainWindowPrivate
{
public:
    dtkInspector *inspector;

public:
    dtkDistributedController *controller;
};

// /////////////////////////////////////////////////////////////////
// tstMainWindow
// /////////////////////////////////////////////////////////////////

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent)
{
    d = new tstMainWindowPrivate;
    d->inspector = NULL;
    d->controller = new dtkDistributedController;

    QAction *inspectorAction = new QAction("Inspector", this);
    inspectorAction->setIcon(QIcon(":dtkGui/pixmaps/dtk-inspector.png"));
    inspectorAction->setShortcut(Qt::ControlModifier + Qt::Key_I);

    QToolBar *toolBar = this->addToolBar("Main");
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->setIconSize(QSize(32, 32));
    toolBar->addWidget(new dtkSpacer(toolBar));
    toolBar->addAction(inspectorAction);

    QObject::connect(inspectorAction, SIGNAL(triggered()), this, SLOT(showInspector()));

    this->setCentralWidget(new QWidget(this));
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setWindowTitle("dtkDistributedController");
}

tstMainWindow::~tstMainWindow(void)
{
    delete d->controller;
    delete d;
}

void tstMainWindow::showInspector(void)
{
    if(!d->inspector) {
        d->inspector = new dtkInspector;

        tstInspectorDistributed *page = new tstInspectorDistributed(d->inspector);

        d->inspector->addPage("Distributed", page);
        d->inspector->setToolBarVisible(true);

        connect(page, SIGNAL(   connect(const QUrl&)), d->controller, SLOT(   connect(const QUrl&)));
        connect(page, SIGNAL(disconnect(const QUrl&)), d->controller, SLOT(disconnect(const QUrl&)));

        connect(d->controller, SIGNAL(   connected(const QUrl&)), page, SLOT(   onConnected(const QUrl&)));
        connect(d->controller, SIGNAL(disconnected(const QUrl&)), page, SLOT(onDisconnected(const QUrl&)));
    }

    d->inspector->setVisible(!d->inspector->isVisible());
}
