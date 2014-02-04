/* dtkComposerStack.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 11:48:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  1 11:43:11 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSTACK_H
#define DTKCOMPOSERSTACK_H

#include <QtWidgets>

class dtkComposerStackCommand;

class dtkComposerStack : public QUndoStack
{
public:
    void push(dtkComposerStackCommand* command);
};

#endif
