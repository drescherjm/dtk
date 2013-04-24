/* dtkComposerQuickNode.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Fri Apr 19 10:18:09 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr 19 11:13:12 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Change Log:
 * 
 */

#include "dtkComposerQuickNode.h"

class dtkComposerQuickNodePrivate
{
public:
    dtkComposerNode *node;

public:
    QString type;
};

dtkComposerQuickNode::dtkComposerQuickNode(QObject *parent) : QObject(parent), d(new dtkComposerQuickNodePrivate)
{
    d->node = NULL;
}

dtkComposerQuickNode::~dtkComposerQuickNode(void)
{
    delete d;
}

void dtkComposerQuickNode::setNode(dtkComposerNode *node)
{
    d->node = node;
}

dtkComposerNode *dtkComposerQuickNode::node(void)
{
    return d->node;
}

const QString& dtkComposerQuickNode::type(void)
{
    return d->type;
}

void dtkComposerQuickNode::setType(const QString& type)
{
    d->type = type;
}
