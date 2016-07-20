/* dtkComposerGraphLayouter.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb 10 10:16:15 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb 10 10:27:11 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 16
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPHLAYOUTER_H
#define DTKCOMPOSERGRAPHLAYOUTER_H

class dtkComposerGraph;
class dtkComposerGraphLayouterPrivate;

class dtkComposerGraphLayouter
{
public:
    dtkComposerGraphLayouter(void);
    ~dtkComposerGraphLayouter(void);

public:
    void setGraph(dtkComposerGraph *graph);

public:
    void layout(void);

private:
    dtkComposerGraphLayouterPrivate *d;
};

#endif
