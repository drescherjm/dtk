/* dtkCreatorViewer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Aug  6 15:47:42 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Aug  6 16:06:40 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 15
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCreatorViewer.h"

#include <QtCore>
#include <QtGui>

class dtkCreatorViewerPrivate
{
public:
    QGridLayout *layout;
};

dtkCreatorViewer::dtkCreatorViewer(QWidget *parent) : QWidget(parent), d(new dtkCreatorViewerPrivate)
{
    d->layout = new QGridLayout(this);
    d->layout->setContentsMargins(1, 1, 1, 1);
    d->layout->setSpacing(1);
}

dtkCreatorViewer::~dtkCreatorViewer(void)
{
    delete d;
    
    d = NULL;
}

void dtkCreatorViewer::attach(QWidget *view, int row, int column, int rspan, int cspan)
{
    view->setParent(this);
    
    d->layout->addWidget(view, row, column, rspan, cspan);
}
