/* dtkComposerNodeFile.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 11:44:04 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  5 09:17:23 2013 (+0200)
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

#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeFilePrivate;

class  dtkComposerNodeFile : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeFile(void);
    ~dtkComposerNodeFile(void);

public:
    void run(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    QString inputLabelHint(int);
    QString outputLabelHint(int);

public:
    QString value(void);

public:
    void setValue(QString value);

private:
    dtkComposerNodeFilePrivate *d;
};

