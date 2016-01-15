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
    virtual void setNode(dtkComposerNode *node);

public:
    dtkComposerNode *node(void);

private:
    class dtkMonitorPrivate *d;
};


template <typename T> dtkMonitor *createMonitor(void)
{
    return new T;
}

//
// dtkMonitor.h ends here
