/* dtkComposerNodeLeafActor.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: jeu. oct. 10 09:56:25 2013 (+0200)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODELEAFACTOR_H
#define DTKCOMPOSERNODELEAFACTOR_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

#include <QObject>

class dtkAbstractActor;
class dtkAbstractView;
class dtkComposerNodeLeafActorPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafActor interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeLeafActor :  public QObject, public dtkComposerNodeLeaf
{
Q_OBJECT

public:
             dtkComposerNodeLeafActor(QObject *parent = 0);
    virtual ~dtkComposerNodeLeafActor(void);

};

#endif
