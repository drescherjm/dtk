/* dtkPlotView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 17:04:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun  1 17:05:02 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
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

dtkPlotView::dtkPlotView(QWidget *parent) : QWidget(parent), d(new dtkPlotViewPrivate)
{

}

dtkPlotView::~dtkPlotView(void)
{
    delete d;

    d = NULL;
}
