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
    // inline QString type(void) {
    //     return "string";
    // }

    // inline QString titleHint(void) {
    //     return "String";
    // }

    // inline QString inputLabelHint(int port) {
    //     if(port == 0)
    //         return "string";

    //     if(port == 1)
    //         return "real";

    //     return "port";
    // }

    // inline QString outputLabelHint(int) {
    //     return "value";
    // }

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
    inline QString type(void) {
        return "StringList";
    }

    inline QString titleHint(void) {
        return "String List";
    }

    inline QString inputLabelHint(int port) {
        if(port == 0)
            return "list";
        if(port == 1)
            return "size";
        if(port == 2)
            return "value";

        return "port";
    }

    inline QString outputLabelHint(int) {
        return "list";
    }

public:
    QStringList value(void);

public:
    void setValue(QStringList value);

private:
    dtkComposerNodeStringListPrivate *d;
};

// 
// dtkComposerNodeString.h ends here
