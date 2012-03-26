/* dtkComposerNodeLogger.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: Mon Mar 26 12:40:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: lun. mars 26 13:28:04 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 18
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
