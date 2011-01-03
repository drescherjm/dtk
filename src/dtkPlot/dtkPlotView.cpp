/* dtkPlotView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Nov 22 10:25:08 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov 22 12:01:38 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 10
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

QBrush dtkPlotView::backgroundBrush(void) const
{
    return QBrush(QColor(29, 29, 29));
}
