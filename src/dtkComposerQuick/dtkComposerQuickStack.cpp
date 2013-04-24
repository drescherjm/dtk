/* dtkComposerQuickStack.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Fri Apr 19 10:59:28 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr 19 11:02:41 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Change Log:
 * 
 */

#include "dtkComposerQuickStack.h"

class dtkComposerQuickStackPrivate
{
public:
    dtkComposerStack *stack;
};

dtkComposerQuickStack::dtkComposerQuickStack(QObject *parent) : QObject(parent), d(new dtkComposerQuickStackPrivate)
{
    d->stack = new dtkComposerStack;
}

dtkComposerQuickStack::~dtkComposerQuickStack(void)
{
    delete d->stack;
    delete d;
}

dtkComposerStack *dtkComposerQuickStack::stack(void)
{
    return d->stack;
}
