/* dtkDistributedApplication.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/02/04 12:28:51
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkDistributedExport.h"

#include <QtCore>

class dtkDistributedCommunicator;
class dtkDistributedPolicy;
class dtkDistributedApplicationPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedApplication: public QCoreApplication
{
public:
             dtkDistributedApplication(int &argc, char **argv);
    virtual ~dtkDistributedApplication(void);

public:
    virtual void initialize(void);
    virtual void exec(QRunnable *task);
    virtual void spawn(QMap<QString, QString> options = QMap<QString, QString>() );
    virtual void unspawn(void);

public:
    QCommandLineParser  *parser(void);

public:
    static dtkDistributedApplication *create(int &argc, char *argv[])
    {
        return new dtkDistributedApplication(argc, argv);
    }

public:
    bool isMaster(void);
    virtual bool noGui(void);
    dtkDistributedCommunicator *communicator(void);
    dtkDistributedPolicy *policy(void);

private:
    dtkDistributedApplicationPrivate *d;

};


