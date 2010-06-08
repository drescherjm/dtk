/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Jun  2 13:58:18 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun  8 11:13:00 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 90
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstMainWindow.h"

#include <dtkGui/dtkInsetMenu.h>
#include <dtkGui/dtkSpacer.h>

// /////////////////////////////////////////////////////////////////
// tstWorkspace
// /////////////////////////////////////////////////////////////////

class tstWorkspacePrivate
{
public:
    dtkInsetMenu *inset;
};

tstWorkspace::tstWorkspace(QWidget *parent) : QWidget(parent), d(new tstWorkspacePrivate)
{
    d->inset = new dtkInsetMenu(this);

    QWidget *contents = new QWidget(this);
    contents->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->inset);
    layout->addWidget(contents);
}

tstWorkspace::~tstWorkspace(void)
{
    delete d;

    d = NULL;
}

dtkInsetMenu *tstWorkspace::inset(void)
{
    return d->inset;
}

void tstWorkspace::toggle(void)
{
    QPropertyAnimation *animation = new QPropertyAnimation(d->inset, "maximumHeight");
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::OutBounce);

    if(!d->inset->height()) {
        animation->setStartValue(d->inset->height());
        animation->setEndValue(100);
    } else {
        animation->setStartValue(d->inset->height());
        animation->setEndValue(0);
    }

    connect(animation, SIGNAL(finished()), animation, SLOT(deleteLater()));

    animation->start();
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class tstMainWindowPrivate
{
public:
    QStackedWidget *stack;

    tstWorkspace *workspace1;
    tstWorkspace *workspace2;
    tstWorkspace *workspace3;
};

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent)
{
    d = new tstMainWindowPrivate;

    d->workspace1 = new tstWorkspace(this);
    d->workspace1->inset()->setStyle(dtkInsetMenu::dtkInsetMenuStyleDefault);
    d->workspace1->inset()->addTab("Tab 1");
    d->workspace1->inset()->addTab("Tab 2");
    d->workspace1->inset()->addItem(0, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace1->inset()->addItem(0, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace1->inset()->addItem(0, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace1->inset()->addItem(1, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace1->inset()->addItem(1, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    
    d->workspace2 = new tstWorkspace(this);
    d->workspace2->inset()->setStyle(dtkInsetMenu::dtkInsetMenuStyleGreen);
    d->workspace2->inset()->addTab("Tab 1");

    d->workspace3 = new tstWorkspace(this);
    d->workspace3->inset()->setStyle(dtkInsetMenu::dtkInsetMenuStyleOrange);
    d->workspace3->inset()->addTab("Tab 1");
    d->workspace3->inset()->addTab("Tab 2");
    d->workspace3->inset()->addTab("Tab 3");
    d->workspace3->inset()->addTab("Tab 4");
    d->workspace3->inset()->addItem(0, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace3->inset()->addItem(0, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace3->inset()->addItem(0, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace3->inset()->addItem(1, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace3->inset()->addItem(1, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace3->inset()->addItem(2, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace3->inset()->addItem(2, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace3->inset()->addItem(2, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace3->inset()->addItem(2, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace3->inset()->addItem(3, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace3->inset()->addItem(3, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace3->inset()->addItem(3, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace3->inset()->addItem(3, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace3->inset()->addItem(3, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));
    d->workspace3->inset()->addItem(3, QPixmap(":dtkGui/pixmaps/dtk-gui-inset-menu-item.png"));

    d->stack = new QStackedWidget(this);
    d->stack->addWidget(d->workspace1);
    d->stack->addWidget(d->workspace2);
    d->stack->addWidget(d->workspace3);

    QAction *workspaceAction1 = new QAction("Workspace1", this);
    workspaceAction1->setIcon(QIcon(":dtkGui/pixmaps/dtk-widget.png"));
    workspaceAction1->setShortcut(Qt::ControlModifier + Qt::Key_1);

    QAction *workspaceAction2 = new QAction("Workspace2", this);
    workspaceAction2->setIcon(QIcon(":dtkGui/pixmaps/dtk-widget.png"));
    workspaceAction2->setShortcut(Qt::ControlModifier + Qt::Key_2);

    QAction *workspaceAction3 = new QAction("Workspace3", this);
    workspaceAction3->setIcon(QIcon(":dtkGui/pixmaps/dtk-widget.png"));
    workspaceAction3->setShortcut(Qt::ControlModifier + Qt::Key_3);

    QAction *insetAction = new QAction("Toggle inset", this);
    insetAction->setIcon(QIcon(":dtkGui/pixmaps/dtk-inset.png"));
    insetAction->setShortcut(Qt::ControlModifier + Qt::Key_3);

    QAction *inspectorAction = new QAction("Inspector", this);
    inspectorAction->setShortcut(Qt::ControlModifier+Qt::Key_I);
    inspectorAction->setToolTip("Show/hide inspector");
    inspectorAction->setIcon(QIcon(":dtkGui/pixmaps/dtk-inspector.png"));

    QToolBar *toolBar = this->addToolBar("Main");
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->setIconSize(QSize(32, 32));
    toolBar->addAction(workspaceAction1);
    toolBar->addAction(workspaceAction2);
    toolBar->addAction(workspaceAction3);
    toolBar->addWidget(new dtkSpacer(toolBar));
    toolBar->addAction(insetAction);
    toolBar->addSeparator();
    toolBar->addAction(inspectorAction);

    this->setCentralWidget(d->stack);
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setWindowTitle("dtkInsetMenu Example");

    connect(workspaceAction1, SIGNAL(triggered()), this, SLOT(switchToWorkspace1()));
    connect(workspaceAction2, SIGNAL(triggered()), this, SLOT(switchToWorkspace2()));
    connect(workspaceAction3, SIGNAL(triggered()), this, SLOT(switchToWorkspace3()));
    connect(insetAction, SIGNAL(triggered()), this, SLOT(toggle()));
}

tstMainWindow::~tstMainWindow(void)
{
    delete d;
}

void tstMainWindow::switchToWorkspace1(void)
{
    d->stack->setCurrentWidget(d->workspace1);
}

void tstMainWindow::switchToWorkspace2(void)
{
    d->stack->setCurrentWidget(d->workspace2);
}

void tstMainWindow::switchToWorkspace3(void)
{
    d->stack->setCurrentWidget(d->workspace3);
}

void tstMainWindow::toggle(void)
{
    switch(d->stack->currentIndex()) {
    case 0: d->workspace1->toggle(); break;
    case 1: d->workspace2->toggle(); break;
    case 2: d->workspace3->toggle(); break;
    default: break;
    }
}
