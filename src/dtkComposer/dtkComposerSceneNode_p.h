/* dtkComposerSceneNode_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 14:15:01 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 15 23:38:01 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 16
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
class dtkComposerSceneNodeComposite;
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
    dtkComposerSceneNodeComposite *parent;

public:
    QString title;
};

#endif
