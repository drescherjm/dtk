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

class dtkMonitor;

class DTKMONITORING_EXPORT dtkMonitoringFactory : public QObject
{
    Q_OBJECT

public:
    typedef dtkMonitor *(*dtkMonitorCreator)(void);

public:
     dtkMonitoringFactory(void);
    ~dtkMonitoringFactory(void);

public:
    void initialize(void);
    void uninitialize(void);

public:
    void registerCreator(const QString& type, dtkMonitorCreator creator);

public slots:
    dtkMonitor *create(const QString& type);

private:
    class dtkMonitoringFactoryPrivate *d;
};

//
// dtkMonitoringFactory.h ends here
