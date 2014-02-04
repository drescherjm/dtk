/* dtkComposerGraphLayouter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb 10 10:16:15 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:23:37 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

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

