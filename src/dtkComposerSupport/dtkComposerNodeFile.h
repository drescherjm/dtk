/* dtkComposerNodeFile.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEFILE_H
#define DTKCOMPOSERNODEFILE_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeFilePrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeFile : public dtkComposerNodeLeaf
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

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeFileExists : public dtkComposerNodeLeaf
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



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFileListDir definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeFileListPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeFileList : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeFileList(void);
    ~dtkComposerNodeFileList(void);

public:
    void run(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    QString inputLabelHint(int);
    QString outputLabelHint(int);

private:
    dtkComposerNodeFileListPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFileRead definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeFileReadPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeFileRead : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeFileRead(void);
    ~dtkComposerNodeFileRead(void);

public:
    void run(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    QString inputLabelHint(int);
    QString outputLabelHint(int);

private:
    dtkComposerNodeFileReadPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFileWrite definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeFileWritePrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeFileWrite : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeFileWrite(void);
    ~dtkComposerNodeFileWrite(void);

public:
    void run(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    QString inputLabelHint(int);
    QString outputLabelHint(int);

private:
    dtkComposerNodeFileWritePrivate *d;
};

#endif
