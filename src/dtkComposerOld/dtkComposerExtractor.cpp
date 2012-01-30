/* dtkComposerExtractor.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Oct  6 19:54:02 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Sat Oct  8 15:13:30 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 39
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerExtractor.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerScene.h"
#include "dtkComposerWriter.h"

class dtkComposerExtractorPrivate
{
public:
    dtkComposerScene *scene;
};

dtkComposerExtractor::dtkComposerExtractor(dtkComposerScene *scene) : d(new dtkComposerExtractorPrivate)
{
    d->scene = scene;
}

dtkComposerExtractor::~dtkComposerExtractor(void)
{
    delete d;

    d = NULL;
}

void dtkComposerExtractor::extract(dtkComposerNode::Attribute attribute)
{
    dtkComposerScene *scene = new dtkComposerScene;

    foreach(dtkComposerNode *node, d->scene->nodes())
        if(node->attribute() == attribute)
            scene->addNode(node);

    foreach(dtkComposerNode *node, scene->nodes())
        foreach(dtkComposerEdge *edge, node->g->rightEdges())
            if(edge->destination()->node()->attribute() == attribute)
                scene->addEdge(edge);

    // QBuffer buffer;

    // dtkComposerWriter *writer = new dtkComposerWriter(d->scene);
    // writer->write(&buffer);

    // delete writer;
    delete scene;
}
