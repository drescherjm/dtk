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

class dtkComposerNodeFilePrivate;

class  DTKCOMPOSER_EXPORT dtkComposerNodeFile : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeFile(void);
    ~dtkComposerNodeFile(void);

public:
    void run(void);

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
    QString value(void);

 public:
    void setValue(QString value);

 private:
    dtkComposerNodeDirectoryPrivate *d;
};

//
// dtkComposerNodeFile.h ends here
