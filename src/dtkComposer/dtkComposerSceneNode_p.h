/* dtkComposerSceneNode_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 14:15:01 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr 10 16:46:14 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 33
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

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

