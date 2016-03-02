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

#pragma once

#include "dtkMonitor.h"

class dtkMonitorInteger : public dtkMonitor
{
public:
     dtkMonitorInteger(QGraphicsItem *parent = 0);
    ~dtkMonitorInteger(void);

public:
    double value(void);

public:
    void setValue(int value);
};

//
// dtkMonitorInteger.h ends here
