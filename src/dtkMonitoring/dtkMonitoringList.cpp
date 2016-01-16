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

#include "dtkMonitoringList.h"

class dtkMonitoringListPrivate
{
public:

};

dtkMonitoringList::dtkMonitoringList(QWidget *parent) : QListView(parent)
{
    d = new dtkMonitoringListPrivate;

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameShape(QFrame::NoFrame);
}

dtkMonitoringList::~dtkMonitoringList(void)
{
    delete d;
}

//
// dtkMonitoringList.cpp ends here
