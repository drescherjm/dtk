/* dtkComposer.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:34:34 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan 31 18:13:36 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSER_H
#define DTKCOMPOSER_H

#include "dtkComposerExport.h"

#include <QtGui/QWidget>

class dtkComposerFactory;
class dtkComposerMachine;
class dtkComposerPrivate;
class dtkComposerStack;

class DTKCOMPOSER_EXPORT dtkComposer : public QWidget
{
    Q_OBJECT

public:
             dtkComposer(QWidget *parent = 0);
    virtual ~dtkComposer(void);

public:
    dtkComposerFactory *factory(void);
    dtkComposerMachine *machine(void);
    dtkComposerStack *stack(void);

private:
    dtkComposerPrivate *d;
};

#endif
