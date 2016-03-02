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
#include "dtkMonitorInteger.h"

class QFocusEvent;

class dtkMonitorIntegerSimple : public dtkMonitorInteger
{
public:
     dtkMonitorIntegerSimple(QGraphicsItem *parent = 0);
    ~dtkMonitorIntegerSimple(void);

public:
    void setNode(dtkComposerNode *node);

public:
    QRectF boundingRect(void) const;

private:
    class dtkMonitorIntegerSimplePrivate *d;

};


//
// dtkMonitorInteger.h ends here
