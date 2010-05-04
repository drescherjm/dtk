/* dtkDistributor.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Mar 21 19:01:19 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr 30 19:06:09 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTOR_H
#define DTKDISTRIBUTOR_H

#include <QtGui>

#include "dtkDistributedExport.h"

class dtkDistributorNode;
class dtkDistributorPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributor : public QWidget
{
    Q_OBJECT

public:
     dtkDistributor(QWidget *parent = 0);
    ~dtkDistributor(void);

protected slots:
    void clear(void);
    void discover(void);
    void update(void);
    void toggle(void);

    void showInformation(dtkDistributorNode *node);
    void hideInformation(dtkDistributorNode *node);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    dtkDistributorPrivate *d;
};

#endif
