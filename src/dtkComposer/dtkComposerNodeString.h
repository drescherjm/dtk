// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:

#pragma once

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

// 
// dtkComposerNodeString.h ends here
