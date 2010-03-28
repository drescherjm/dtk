/* dtkDistributorInset.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Mar 25 13:10:54 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Mar 27 18:07:07 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 25
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTORINSET_H
#define DTKDISTRIBUTORINSET_H

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkDistributorInsetPixmap
// /////////////////////////////////////////////////////////////////

class dtkDistributorInsetPixmap : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
     dtkDistributorInsetPixmap(const QPixmap& pixmap, QGraphicsItem *parent = 0);
    ~dtkDistributorInsetPixmap(void);
};

// /////////////////////////////////////////////////////////////////
// dtkDistributorInsetHeader
// /////////////////////////////////////////////////////////////////

class dtkDistributorInsetHeader : public QFrame
{
    Q_OBJECT

public:
     dtkDistributorInsetHeader(QWidget *parent);
    ~dtkDistributorInsetHeader(void);

signals:
    void buttonClicked(int);
};

// /////////////////////////////////////////////////////////////////
// dtkDistributorInsetBody
// /////////////////////////////////////////////////////////////////

class dtkDistributorInsetBodyPrivate;

class dtkDistributorInsetBody : public QFrame
{
    Q_OBJECT

public:
     dtkDistributorInsetBody(QWidget *parent);
    ~dtkDistributorInsetBody(void);

public slots:
    void setCurrentIndex(int index);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    dtkDistributorInsetBodyPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributorInset
// /////////////////////////////////////////////////////////////////

class dtkDistributorInsetPrivate;

class dtkDistributorInset : public QFrame
{
    Q_OBJECT

public:
     dtkDistributorInset(QWidget *parent);
    ~dtkDistributorInset(void);

private:
    dtkDistributorInsetPrivate *d;
};

#endif
