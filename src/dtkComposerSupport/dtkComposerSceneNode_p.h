/* dtkComposerSceneNode_p.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 14:15:01 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 16 18:13:20 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 31
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERSCENENODE_P_H
#define DTKCOMPOSERSCENENODE_P_H

#include <QtCore>

#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerScenePort.h"

class dtkComposerNode;

class dtkComposerSceneNodePrivate
{
public:
    dtkComposerNode *wrapee;

public:
    dtkComposerScenePortList  input_ports;
    dtkComposerScenePortList output_ports;

    dtkComposerSceneEdgeList  input_edges;
    dtkComposerSceneEdgeList output_edges;

public:
    dtkComposerSceneNode *parent;

public:
    QString title;

public:
    bool embedded;
};

#endif
