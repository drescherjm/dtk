/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar 23 21:05:20 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 14 15:38:44 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 53
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui>

#include "tstInspectorObject.h"
#include "tstInspectorScene.h"
#include "tstMainWindow.h"

#include <dtkGui/dtkInspector.h>
#include <dtkGui/dtkSpacer.h>

// /////////////////////////////////////////////////////////////////
// tstMainWindowPrivate
// /////////////////////////////////////////////////////////////////

class tstMainWindowPrivate
{
public:
    dtkInspector *inspector;
};

// /////////////////////////////////////////////////////////////////
// tstMainWindow
// /////////////////////////////////////////////////////////////////


tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent)
{
    d = new tstMainWindowPrivate;
    d->inspector = NULL;

    QAction *inspectorAction = new QAction("Inspector", this);
    inspectorAction->setIcon(QIcon(":dtkGui/pixmaps/dtk-inspector.png"));
    inspectorAction->setShortcut(Qt::ControlModifier + Qt::Key_I);

    QToolBar *toolBar = this->addToolBar("Main");
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->setIconSize(QSize(32, 32));
    toolBar->addWidget(new dtkSpacer(toolBar));
    toolBar->addAction(inspectorAction);

    connect(inspectorAction, SIGNAL(triggered()), this, SLOT(showInspector()));

    this->setCentralWidget(new QWidget(this));
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setWindowTitle("dtkInspector");
}

tstMainWindow::~tstMainWindow(void)
{
    delete d;
}

void tstMainWindow::showInspector(void)
{
    if(!d->inspector) {
        d->inspector = new dtkInspector;
        d->inspector->addPage("Scene", new tstInspectorScene(d->inspector));
        d->inspector->addPage("Object", new tstInspectorObject(d->inspector));
    }

    d->inspector->setVisible(!d->inspector->isVisible());
}
