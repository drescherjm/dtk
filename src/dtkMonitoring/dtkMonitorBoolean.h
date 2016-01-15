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

class dtkMonitorBoolean : public dtkMonitor
{
public:
     dtkMonitorBoolean(QGraphicsItem *parent = 0);
    ~dtkMonitorBoolean(void);

public:
    bool value(void);
    void setValue(bool value);
};


//
// dtkMonitorBoolean.h ends here
