/* dtkDistributor.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Mar 21 19:01:19 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr  1 10:45:16 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 19
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

class dtkDistributorNode;
class dtkDistributorPrivate;

class dtkDistributor : public QWidget
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
