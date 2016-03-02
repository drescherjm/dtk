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
#include "dtkMonitorReal.h"

class QFocusEvent;

class dtkMonitorRealSimple : public dtkMonitorReal
{
public:
     dtkMonitorRealSimple(QGraphicsItem *parent = 0);
    ~dtkMonitorRealSimple(void);

public:
    void setNode(dtkComposerNode *node);

public:
    QRectF boundingRect(void) const;

protected:
    void focusInEvent(QFocusEvent * event);

private:
    class dtkMonitorRealSimplePrivate *d;

};


//
// dtkMonitorReal.h ends here
