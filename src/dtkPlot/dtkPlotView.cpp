/* dtkPlotView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 17:04:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jun  6 16:14:16 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 4
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
