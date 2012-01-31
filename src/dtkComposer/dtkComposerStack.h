/* dtkComposerStack.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 11:48:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan 31 18:23:37 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSTACK_H
#define DTKCOMPOSERSTACK_H

#include <QtGui>

class dtkComposerStackCommand;

class dtkComposerStack : public QUndoStack
{
public:
    void push(dtkComposerStackCommand* command);
};

#endif
