/* @(#)dtkComposerGraphNodeSelectBranch.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: ven. mars  2 18:33:14 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 139
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeSelectBranch.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"

//#include <dtkLog/dtkLog.h>

#include <QVarLengthArray>

class dtkComposerGraphNodeSelectBranchPrivate
{
public:
    dtkComposerNodeControl *composer_node;

public:
    static const int DEFAULT_SIZE = 16;

public:
    QVarLengthArray<dtkComposerGraphNode *,DEFAULT_SIZE> successors;

public:
    int result;
};


dtkComposerGraphNodeSelectBranch::dtkComposerGraphNodeSelectBranch(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeSelectBranchPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
    this->setTitle(title);
    this->setStatus(dtkComposerGraphNode::Ready);
    d->result =-1;
}


dtkComposerNode *dtkComposerGraphNodeSelectBranch::wrapee(void)
{
    return d->composer_node;
}

dtkComposerGraphNode::Kind dtkComposerGraphNodeSelectBranch::kind(void)
{
    return dtkComposerGraphNode::SelectBranch;
}

void dtkComposerGraphNodeSelectBranch::addSuccessor(dtkComposerGraphNode *node, int id)
{
    if (id > dtkComposerGraphNodeSelectBranchPrivate::DEFAULT_SIZE)
        d->successors.resize(id*4); //FIXME

    d->successors[id]=node;
}


void dtkComposerGraphNodeSelectBranch::removeSuccessor(dtkComposerGraphNode *node)
{
    for (int i=0; i < d->successors.size(); i++)
        if (d->successors[i] == node)
            d->successors[i] = NULL;
}

dtkComposerGraphNodeList dtkComposerGraphNodeSelectBranch::successors(void)
{
    dtkComposerGraphNodeList val;
    if (d->result < 0) {
        for (int i=0; i < d->successors.size(); i++)
            val << d->successors[i];
        return val;
    } else if (d->result < d->successors.size())
        return val << d->successors[d->result];
    else
//        dtkError() << "Select branch result is out of bound:" << d->result;
        return val;
}

void dtkComposerGraphNodeSelectBranch::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->result = d->composer_node->selectBranch();
}


