/* dtkComposerStack.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 18:23:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Apr 15 11:35:29 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerStack.h"
#include "dtkComposerStackCommand.h"

void dtkComposerStack::push(dtkComposerStackCommand *command)
{
    QUndoStack::push(command);
}
