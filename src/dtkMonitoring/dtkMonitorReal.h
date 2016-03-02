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

class dtkMonitorReal : public dtkMonitor
{
public:
     dtkMonitorReal(QGraphicsItem *parent = 0);
    ~dtkMonitorReal(void);

public:
    double value(void);

public:
    void setValue(double value);
};

//
// dtkMonitorReal.h ends here
