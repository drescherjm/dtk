/* dtkViewLayout.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:38:08 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 16 09:38:11 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVIEWLAYOUT_H
#define DTKVIEWLAYOUT_H

#include <QtGui>

class dtkViewLayoutPrivate;

class dtkViewLayout : public QFrame
{
    Q_OBJECT

public:
     dtkViewLayout(QWidget *parent = 0);
    ~dtkViewLayout(void);

private:
    dtkViewLayoutPrivate *d;
};

#endif // DTKVIEWLAYOUT_H
