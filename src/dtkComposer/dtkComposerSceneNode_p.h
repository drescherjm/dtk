/* dtkComposerSceneNode_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 14:15:01 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 16 12:57:01 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 19
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

class dtkComposerNode;
class dtkComposerSceneEdge;
class dtkComposerSceneNode;
class dtkComposerScenePort;

class dtkComposerSceneNodePrivate
{
public:
    dtkComposerNode *wrapee;

public:
    QList<dtkComposerScenePort *>  input_ports;
    QList<dtkComposerScenePort *> output_ports;

    QList<dtkComposerSceneEdge *>  input_edges;
    QList<dtkComposerSceneEdge *> output_edges;

public:
    dtkComposerSceneNode *parent;

public:
    QString title;
};

#endif
