/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Jun 12 15:54:21 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Sat Jun 12 16:13:03 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstMainWindow.h"

#include <dtkGui/dtkAnchoredBar.h>
#include <dtkGui/dtkFinder.h>

class tstMainWindowPrivate
{
public:
    dtkFinder *finder;
    dtkFinderPathBar *path;
    dtkFinderSideView *side;
};

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent), d(new tstMainWindowPrivate)
{
    d->finder = new dtkFinder(this);

    d->path = new dtkFinderPathBar(this);
    d->path->setPath(QDir::currentPath());

    d->side = new dtkFinderSideView(this);

    QWidget *side = new QWidget(this);
    side->setMaximumWidth(200);

    dtkAnchoredBar *anchoredBar = new dtkAnchoredBar(side);

    QVBoxLayout *side_layout = new QVBoxLayout(side);
    side_layout->setContentsMargins(0, 0, 0, 0);
    side_layout->setSpacing(0);
    side_layout->addWidget(d->side);
    side_layout->addWidget(anchoredBar);

    QWidget *main = new QWidget(this);

    QVBoxLayout *main_layout = new QVBoxLayout(main);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setSpacing(0);
    main_layout->addWidget(d->finder);
    main_layout->addWidget(d->path);

    QWidget *central = new QWidget(this);

    QHBoxLayout *layout= new QHBoxLayout(central);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(side);
    layout->addWidget(main);

    this->setCentralWidget(central);

    connect(d->finder, SIGNAL(changed(QString)), d->path, SLOT(setPath(QString)));
    connect(d->finder, SIGNAL(changed(QString)), d->side, SLOT(setPath(QString)));

    connect(d->path, SIGNAL(changed(QString)), d->finder, SLOT(setPath(QString)));
    connect(d->path, SIGNAL(changed(QString)), d->side, SLOT(setPath(QString)));

    connect(d->side, SIGNAL(changed(QString)), d->finder, SLOT(setPath(QString)));
    connect(d->side, SIGNAL(changed(QString)), d->path, SLOT(setPath(QString)));

    connect(d->finder, SIGNAL(bookmarked(QString)), d->side, SLOT(addBookmark(QString)));

    QAction *clearBookmarksAction = new QAction("Clear bookmarks", this);
    clearBookmarksAction->setShortcut(Qt::ControlModifier + Qt::ShiftModifier + Qt::Key_C);
    anchoredBar->addAction(clearBookmarksAction);
    anchoredBar->addSeparator();
    connect(clearBookmarksAction, SIGNAL(triggered()), d->side, SLOT(clearBookmarks()));

    this->setUnifiedTitleAndToolBarOnMac(true);
}

tstMainWindow::~tstMainWindow(void)
{
    delete d;

    d = NULL;
}
