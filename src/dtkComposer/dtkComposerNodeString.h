/* dtkComposerNodeString.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:50:23 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODESTRING_H
#define DTKCOMPOSERNODESTRING_H

#include "dtkComposerExport.h"

#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeStringPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeString : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeString(void);
    ~dtkComposerNodeString(void);

public:
    void run(void);

public:
    QString value(void);

public:
    void setValue(QString value);

private:
    dtkComposerNodeStringPrivate *d;
};


class dtkComposerNodeStringListPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeStringList : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeStringList(void);
    ~dtkComposerNodeStringList(void);

public:
    void run(void);

public:
    QStringList value(void);

public:
    void setValue(QStringList value);

private:
    dtkComposerNodeStringListPrivate *d;
};


#endif
