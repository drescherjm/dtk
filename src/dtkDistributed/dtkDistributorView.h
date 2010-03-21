/* dtkDistributorView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Mar 21 18:24:47 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar 21 19:06:44 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTORVIEW_H
#define DTKDISTRIBUTORVIEW_H

#include <QtGui>

class dtkDistributorViewPrivate;

class dtkDistributorView : public QGraphicsView
{
    Q_OBJECT

public:
     dtkDistributorView(QWidget *parent = 0);
    ~dtkDistributorView(void);

private:
    dtkDistributorViewPrivate *d;
};

#endif
