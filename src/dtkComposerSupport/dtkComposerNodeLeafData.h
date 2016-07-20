/* dtkComposerNodeLeafData.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jun 28 09:56:37 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2012 Fri Nov 16 15:49:52 (+0100)
 *           By: Thibaud Kloczko, Inria.
 *     Update #: 41
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODELEAFDATA_H
#define DTKCOMPOSERNODELEAFDATA_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

#include <QStringList>

class dtkAbstractData;
class dtkComposerNodeLeafDataPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafData interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeLeafData : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeLeafData(void);
    virtual ~dtkComposerNodeLeafData(void);

public:
    virtual bool enableDefaultImplementation(void) const;

    virtual bool isAbstractData(void) const = 0;

    virtual QString abstractDataType(void) const = 0;

public:
    bool implementationHasChanged(void) const;

    QString currentImplementation(void);

    QStringList implementations(void);

public:
    dtkAbstractData *createData(const QString& implementation);

    dtkAbstractData *data(void);

private:
    dtkComposerNodeLeafDataPrivate *d;
};

#endif
