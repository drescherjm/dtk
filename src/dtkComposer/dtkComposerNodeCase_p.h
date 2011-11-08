/* dtkComposerNodeCase_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Mar  4 21:57:30 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Nov  8 15:53:39 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 23
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
#include <QtCore/QString>

class dtkComposerNodeCase;
class dtkComposerNodeCaseButton;
class dtkComposerNodeControlBlock;

class dtkComposerNodeCasePrivate
{
public:
    void createBlock(const QString& title, dtkComposerNodeCase *parent);

public:
    dtkComposerNodeCaseButton *add_button;

public:
    QList<QVariant> constants;
};

#endif
