/* dtkComposerNodeLeafData.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jun 28 09:56:37 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:58:25 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 43
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerNodeLeaf.h"

#include <QStringList>

class dtkAbstractData;
class dtkComposerNodeLeafDataPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafData interface
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeLeafData : public dtkComposerNodeLeaf
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

