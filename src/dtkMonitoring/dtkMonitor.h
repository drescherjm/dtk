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

#include <QtWidgets>

#include "dtkMonitoringExport.h"

class DTKMONITORING_EXPORT dtkMonitor : public QGraphicsItem
{
public:
     dtkMonitor(QGraphicsItem *parent = 0);
    ~dtkMonitor(void);

public:
    virtual QString identifier(void) = 0;
};

//
// dtkMonitor.h ends here
