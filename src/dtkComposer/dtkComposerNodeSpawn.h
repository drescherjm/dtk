/* dtkComposerNodeSpawn.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2013/09/30 17:15:12
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODESPAWN_H
#define DTKCOMPOSERNODESPAWN_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeRemote.h"
#include "dtkComposerNodeLeaf.h"

#include <QDomDocument>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeSpawn declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeSpawnPrivate;
class dtkDistributedCommunicator;
class dtkDistributedController;
class dtkDistributedSlave;

class DTKCOMPOSER_EXPORT dtkComposerNodeSpawn : public dtkComposerNodeRemote
{
    Q_OBJECT

public:
             dtkComposerNodeSpawn(void);
    virtual ~dtkComposerNodeSpawn(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    void setApplication(QString app);
    void setComposition(QDomDocument document);
    void setCommunicator(dtkDistributedCommunicator *comm);
    void setInternalCommunicator(dtkDistributedCommunicator *comm);

public:
    bool isSlave(void);

public:
    virtual void begin(void);
    virtual void end(void);

private:
    dtkComposerNodeSpawnPrivate *d;
};


#endif /* DTKCOMPOSERNODEREMOTE_H */
