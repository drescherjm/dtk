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


#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeLoggerPrivate;

class  dtkComposerNodeLogger : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeLogger(void);
    ~dtkComposerNodeLogger(void);

public:
    void run(void);

private:
    dtkComposerNodeLoggerPrivate *d;
};

#endif
