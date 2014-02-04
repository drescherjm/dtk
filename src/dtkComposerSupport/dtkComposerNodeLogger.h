/* dtkComposerNodeLogger.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: Mon Mar 26 12:40:45 2012 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODELOGGER_H
#define DTKCOMPOSERNODELOGGER_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeLoggerPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeLogger : public dtkComposerNodeLeaf
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
        if (port == 0)
            return "value";
        else if (port == 1)
            return "header";
        else if (port == 2)
            return "level";
        else
            return "value";
    }

private:
    dtkComposerNodeLoggerPrivate *d;
};

#endif
