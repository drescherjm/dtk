/* dtkComposerStack.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 11:48:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. oct. 23 15:31:11 2014 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 21
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include <QtWidgets>

class dtkComposerStackCommand;

class DTKCOMPOSER_EXPORT dtkComposerStack : public QUndoStack
{
public:
    void push(dtkComposerStackCommand* command);
};


