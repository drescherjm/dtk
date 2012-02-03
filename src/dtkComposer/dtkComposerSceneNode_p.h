/* dtkComposerSceneNode_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 14:15:01 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  3 14:15:53 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 6
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

class dtkComposerSceneEdge;
class dtkComposerScenePort;

class dtkComposerSceneNodePrivate
{
public:
    QList<dtkComposerScenePort *>  input_ports;
    QList<dtkComposerScenePort *> output_ports;

    QList<dtkComposerSceneEdge *>  input_edges;
    QList<dtkComposerSceneEdge *> output_edges;
};

#endif
