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

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeStringPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeString : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeString(void);
    ~dtkComposerNodeString(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "string";
    }

    inline QString titleHint(void) {
        return "String";
    }

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "string";

        if (port == 1)
            return "real";

        return dtkComposerNodeLeaf::inputLabelHint(port);
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

public:
    QString value(void);

public:
    void setValue(QString value);

private:
    dtkComposerNodeStringPrivate *d;
};


class dtkComposerNodeStringListPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeStringList : public dtkComposerNodeLeaf
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
        if (port == 0)
            return "list";

        if (port == 1)
            return "size";

        if (port == 2)
            return "value";

        return dtkComposerNodeLeaf::inputLabelHint(port);
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


#endif
