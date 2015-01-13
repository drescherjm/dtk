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

// 
// dtkComposerNodeSpawn.h ends here
