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

class dtkComposerNode;

class DTKMONITORING_EXPORT dtkMonitor : public QGraphicsItem
{
public:
     dtkMonitor(QGraphicsItem *parent = 0);
    ~dtkMonitor(void);

public:
    void setNode(dtkComposerNode *node);

public:
    dtkComposerNode node(void);

private:
    class dtkMonitorPrivate *d;
};

//
// dtkMonitor.h ends here
