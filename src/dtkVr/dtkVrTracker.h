/* dtkVrTracker.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 20:30:26 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 18 20:31:52 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRTRACKER_H
#define DTKVRTRACKER_H

#include "dtkVrExport.h"

#include <QtCore>

class dtkVrTrackerPrivate;

class DTKVR_EXPORT dtkVrTracker : public QObject
{
    Q_OBJECT

public:
     dtkVrTracker(void);
    ~dtkVrTracker(void);

private:
    dtkVrTrackerPrivate *d;
};

#endif
