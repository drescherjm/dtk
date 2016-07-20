/* dtkComposerGraphEdge.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:08:41 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:22:37 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 59
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <QtCore>

#include <dtkMath/dtkGraphEdge.h>
#include "dtkComposerGraphNode.h"

class dtkComposerGraphEdgePrivate;
class dtkGraphEdge;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphEdge
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphEdge : public dtkGraphEdge
{
public:
    dtkComposerGraphEdge(void);
    ~dtkComposerGraphEdge(void);

public:
    dtkComposerGraphNode *source(void) const ;
    dtkComposerGraphNode *destination(void) const;

public:
    int id(void);

public:
    void setId(int id);

private:
    dtkComposerGraphEdgePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphEdgeList
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphEdgeList : public QList<dtkComposerGraphEdge *>
{
public:
    dtkComposerGraphEdgeList(void);
    dtkComposerGraphEdgeList(const QList<dtkComposerGraphEdge *>& other);
};

