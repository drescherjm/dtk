/* dtkComposerEvaluatorProcess.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2013/10/07 10:23:58
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerExport.h"

#include <dtkDistributed/dtkDistributedWork.h>

#include <QtCore>

class dtkComposerNodeFactory;
class dtkDistributedCommunicator;
class dtkComposerEvaluatorProcessPrivate;

class DTKCOMPOSER_EXPORT dtkComposerEvaluatorProcess : public dtkDistributedWork
{
    Q_OBJECT

public:
     dtkComposerEvaluatorProcess(void);
    ~dtkComposerEvaluatorProcess(void);

public:
    dtkComposerEvaluatorProcess *clone(void);

public:
    void setApplication(QString app);
    void setFactory(dtkComposerNodeFactory *factory);
    void setInternalCommunicator(dtkDistributedCommunicator *communicator);
    void setParentCommunicator(dtkDistributedCommunicator *communicator);

public:
    int run(void);

private:
    dtkComposerEvaluatorProcessPrivate *d;
};
