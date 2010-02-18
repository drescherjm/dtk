/* dtkVrTracker.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 20:32:08 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 18 22:42:35 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrTracker.h"

class dtkVrTrackerPrivate
{
public:
};

dtkVrTracker::dtkVrTracker(void) : QObject(), d(new dtkVrTrackerPrivate)
{

}

dtkVrTracker::~dtkVrTracker(void)
{
    delete d;

    d = NULL;
}
