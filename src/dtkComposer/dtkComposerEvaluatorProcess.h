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

#include <QtCore>

class dtkComposerNodeFactory;
class dtkDistributedCommunicator;
class dtkComposerEvaluatorProcessPrivate;

class DTKCOMPOSER_EXPORT dtkComposerEvaluatorProcess : public QObject, public QRunnable
{
    Q_OBJECT

public:
     dtkComposerEvaluatorProcess(void);
    ~dtkComposerEvaluatorProcess(void);

public:
    void setApplication(QString app);
    void setFactory(dtkComposerNodeFactory *factory);
    void setInternalCommunicator(dtkDistributedCommunicator *communicator);
    void setParentCommunicator(dtkDistributedCommunicator *communicator);

public:
    void run(void);
    int exec(void);

private:
    dtkComposerEvaluatorProcessPrivate *d;
};
