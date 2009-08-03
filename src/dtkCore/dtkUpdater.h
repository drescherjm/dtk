/* dtkUpdater.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jul 20 11:15:03 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jul 20 11:15:07 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKUPDATER_H
#define DTKUPDATER_H

#include <QtCore>

class dtkUpdaterPrivate;

class dtkUpdater
{   
public:
     dtkUpdater(const QUrl& url);
    ~dtkUpdater(void);

private:
    dtkUpdaterPrivate *d;
};

#endif // DTKUPDATER_H
