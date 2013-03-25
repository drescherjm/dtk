/* dtkComposerStack.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 11:48:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 25 09:16:53 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include <QtGui>
#include <QtWidgets>

class dtkComposerStackCommand;

class dtkComposerStack : public QUndoStack
{
public:
    void push(dtkComposerStackCommand* command);
};


