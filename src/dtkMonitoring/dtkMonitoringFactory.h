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
    typedef dtkMonitor *(*dtkMonitorCreator)(const QString& type);

public:
    static dtkMonitoringFactory *instance(void);

public:
    void registerCreator(const QString& type, dtkMonitorCreator creator);

public slots:
    dtkMonitor *create(const QString& type);

private:
     dtkMonitoringFactory(void);
    ~dtkMonitoringFactory(void);

private:
    static dtkMonitoringFactory *s_instance;

private:
    class dtkMonitoringFactoryPrivate *d;
};

//
// dtkMonitoringFactory.h ends here
