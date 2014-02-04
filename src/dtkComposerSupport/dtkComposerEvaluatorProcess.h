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

#ifndef DTKCOMPOSEREVALUATORPROCESS_H
#define DTKCOMPOSEREVALUATORPROCESS_H

#include "dtkComposerSupportExport.h"
#include <QtCore>

class dtkComposerFactory;
class dtkDistributedCommunicator;
class dtkComposerEvaluatorProcessPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerEvaluatorProcess : public QObject
{
    Q_OBJECT

public:
     dtkComposerEvaluatorProcess(void);
    ~dtkComposerEvaluatorProcess(void);

public:
    void setApplication(QString app);
    void setFactory(dtkComposerFactory *factory);
    void setInternalCommunicator(dtkDistributedCommunicator *communicator);
    void setParentCommunicator(dtkDistributedCommunicator *communicator);

public:
    int exec(void);

private:
    dtkComposerEvaluatorProcessPrivate *d;
};


#endif /* DTKCOMPOSEREVALUATORPROCESS_H */

