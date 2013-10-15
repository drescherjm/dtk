/* dtkComposerNodeFile.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 11:44:04 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. oct. 15 15:24:49 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 25
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEFILE_H
#define DTKCOMPOSERNODEFILE_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeFilePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeFile : public dtkComposerNodeLeaf
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


class dtkComposerNodeFileExistsPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeFileExists : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeFileExists(void);
    ~dtkComposerNodeFileExists(void);

public:
    void run(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    QString inputLabelHint(int);
    QString outputLabelHint(int);

private:
    dtkComposerNodeFileExistsPrivate *d;
};

#endif
