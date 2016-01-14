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

#include <QtCore>

#include "dtkMonitoringExport.h"

class dtkComposerNode;

class DTKMONITORING_EXPORT dtkMonitoringController : public QObject
{
    Q_OBJECT

public:
    static dtkMonitoringController *instance(void);

public:
    void registerNode(dtkComposerNode *);

public:
    int nodeCount() const;
    QList<dtkComposerNode*> nodeList() const;

private:
     dtkMonitoringController(void);
    ~dtkMonitoringController(void);

private:
    static dtkMonitoringController *s_instance;

private:
    class dtkMonitoringControllerPrivate *d;
};

//
// dtkMonitoringController.h ends here
