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

class DTKMONITORING_EXPORT dtkMonitoringView : public QGraphicsView
{
    Q_OBJECT

public:
             dtkMonitoringView(QWidget *parent = 0);
    virtual ~dtkMonitoringView(void);

private:
    class dtkMonitoringViewPrivate *d;
};

//
// dtkMonitoringView.h ends here
