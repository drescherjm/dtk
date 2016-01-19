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

class dtkMonitoringModel;

class DTKMONITORING_EXPORT dtkMonitoringList : public QListView
{
    Q_OBJECT

public:
     dtkMonitoringList(QWidget *parent);
    ~dtkMonitoringList(void);

public:
     void setModel(dtkMonitoringModel *model);


private:
    class dtkMonitoringListPrivate *d;
};

//
// dtkMonitoringList.h ends here
