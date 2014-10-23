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

#include "dtkComposerExport.h"

#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeFilePrivate;

class  DTKCOMPOSER_EXPORT dtkComposerNodeFile : public dtkComposerNodeLeaf
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



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFileListDir definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeFileListPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeFileList : public dtkComposerNodeLeaf
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

class DTKCOMPOSER_EXPORT dtkComposerNodeFileRead : public dtkComposerNodeLeaf
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

class DTKCOMPOSER_EXPORT dtkComposerNodeFileWrite : public dtkComposerNodeLeaf
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


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeDirectory definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeDirectoryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeDirectory : public dtkComposerNodeLeaf
{
 public:
    dtkComposerNodeDirectory(void);
    ~dtkComposerNodeDirectory(void);

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
    dtkComposerNodeDirectoryPrivate *d;
};
