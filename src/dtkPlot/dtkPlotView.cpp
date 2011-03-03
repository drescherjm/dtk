/* dtkPlotView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Nov 22 10:25:08 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 17 12:49:01 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotView.h"

class dtkPlotViewPrivate
{
public:

};

dtkPlotView::dtkPlotView(QWidget *parent) : QGraphicsView(parent), d(new dtkPlotViewPrivate)
{
    this->setRenderHints(QPainter::Antialiasing);
}

dtkPlotView::~dtkPlotView(void)
{
    delete d;

    d = NULL;
}
