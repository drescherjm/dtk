/* @(#)dtkComposerGraphNodeSelectBranch.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: Wed Mar 20 14:43:49 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 206
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

#include <dtkLog/dtkLogger.h>

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
    d->successors.resize(dtkComposerGraphNodeSelectBranchPrivate::DEFAULT_SIZE);
    for (int i = 0; i < dtkComposerGraphNodeSelectBranchPrivate::DEFAULT_SIZE; i++)
        d->successors[i] = NULL;
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

dtkComposerGraphNode *dtkComposerGraphNodeSelectBranch::firstSuccessor(void)
{
    if (d->result >= 0)
        return d->successors[d->result];
    else {
        dtkError() << "Unknown first successor";
        return NULL;
    }
}

dtkComposerGraphNodeList dtkComposerGraphNodeSelectBranch::successors(void)
{
    dtkComposerGraphNodeList val;
    if (d->result >= 0  && d->result < d->successors.size())
        val << d->successors[d->result];
    else {
        int i = 0;
        do {
            val << d->successors[i];
            i++;
        } while (d->successors[i] != NULL);
    }
    return val;
}

void dtkComposerGraphNodeSelectBranch::clean(void) 
{
    d->result = -1;
    dtkComposerGraphNode::clean();
}

void dtkComposerGraphNodeSelectBranch::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->result = d->composer_node->selectBranch();
    this->setStatus(dtkComposerGraphNode::Done);
}


