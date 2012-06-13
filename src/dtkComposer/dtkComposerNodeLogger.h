/* dtkComposerNodeLogger.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: Mon Mar 26 12:40:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr  3 16:06:32 2012 (+0200)
 *           By: tkloczko
 *     Update #: 20
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODELOGGER_H
#define DTKCOMPOSERNODELOGGER_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeLoggerPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeLogger : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeLogger(void);
    ~dtkComposerNodeLogger(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "logger";
    }

    inline QString titleHint(void) {
        return "Logger";
    }

    inline QString inputLabelHint(int port) {
        return "value";
    }

private:
    dtkComposerNodeLoggerPrivate *d;
};

#endif
