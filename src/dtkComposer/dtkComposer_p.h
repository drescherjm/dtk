/* dtkComposer_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:35:09 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan 31 18:11:23 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 48
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSER_P_H
#define DTKCOMPOSER_P_H

#include <QtCore>

class dtkComposerFactory;
class dtkComposerMachine;
class dtkComposerScene;
class dtkComposerStack;
class dtkComposerView;

class dtkComposerPrivate
{
public:
    dtkComposerFactory *factory;
    dtkComposerMachine *machine;
    dtkComposerScene *scene;
    dtkComposerStack *stack;
    dtkComposerView *view;
};

#endif
