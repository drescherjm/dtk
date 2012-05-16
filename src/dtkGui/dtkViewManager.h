/* dtkViewManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:37:32 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 16 09:37:36 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVIEWMANAGER_H
#define DTKVIEWMANAGER_H

#include <QFrame>

class dtkViewManagerPrivate;

class dtkViewManager : public QFrame
{
    Q_OBJECT

public:
     dtkViewManager(QWidget *parent = 0);
    ~dtkViewManager(void);
    
private:
    dtkViewManagerPrivate *d;
};

#endif
