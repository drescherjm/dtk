/* dtkComposerNodeCase_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Mar  4 21:57:30 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Mar  4 21:58:30 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECASE_P_H
#define DTKCOMPOSERNODECASE_P_H

#include <QtCore/QList>

class dtkComposerNodeCaseButton;
class dtkComposerNodeControlBlock;

class dtkComposerNodeCasePrivate
{
public:
    dtkComposerNodeCaseButton *button;

public:
    QList<dtkComposerNodeControlBlock *> block_cases;
          dtkComposerNodeControlBlock *  block_default;
};

#endif
