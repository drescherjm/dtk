// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkMonitoringView.h"

class dtkMonitoringViewPrivate
{
public:
};

dtkMonitoringView::dtkMonitoringView(QWidget *parent) : QGraphicsView(parent)
{
    d = new dtkMonitoringViewPrivate;
}

dtkMonitoringView::~dtkMonitoringView(void)
{
    delete d;
}

//
// dtkMonitoringView.cpp ends here