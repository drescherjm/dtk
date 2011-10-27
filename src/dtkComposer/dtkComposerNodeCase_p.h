/* dtkComposerNodeCase_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Mar  4 21:57:30 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Oct 26 17:22:43 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 13
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
    dtkComposerNodeCaseButton *add_button;

public:
    QList<dtkComposerNodeControlBlock *> block_cases;
          dtkComposerNodeControlBlock *  block_default;

public:
    QList<QVariant> constants;
};

#endif
