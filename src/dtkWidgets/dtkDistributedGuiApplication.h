/* @(#)dtkDistributedGuiApplication.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/04/25 13:04:29
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkWidgetsExport.h"

#include "dtkApplication.h"

class dtkDistributedCommunicator;
class dtkDistributedPolicy;
class dtkDistributedApplicationPrivate;

class DTKWIDGETS_EXPORT dtkDistributedGuiApplication: public dtkApplication
{
public:
             dtkDistributedGuiApplication(int &argc, char **argv);
    virtual ~dtkDistributedGuiApplication(void);

public:
    virtual void initialize(void);
    virtual void exec(QRunnable *task);
    virtual void spawn(QMap<QString, QString> options = QMap<QString, QString>() );
    virtual void unspawn(void);

public:
    bool isMaster(void);
    dtkDistributedCommunicator *communicator(void);
    dtkDistributedPolicy *policy(void);

private:
    dtkDistributedApplicationPrivate *d;

};





