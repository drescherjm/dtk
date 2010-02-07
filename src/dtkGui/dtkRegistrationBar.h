/* dtkRegistrationBar.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb  7 15:11:08 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb  7 15:13:06 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKREGISTRATIONBAR_H
#define DTKREGISTRATIONBAR_H

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkRegistrationBarButton
// /////////////////////////////////////////////////////////////////

class dtkRegistrationBarButtonPrivate;

class dtkRegistrationBarButton : public QAbstractButton
{
    Q_OBJECT
    
public:
     dtkRegistrationBarButton(QWidget *parent = 0);
     dtkRegistrationBarButton(const QString& text, QWidget *parent = 0);
    ~dtkRegistrationBarButton(void);
    
public:
    void setRadius(qreal radius);
    void setRadius(qreal leftTopRadius, qreal leftBottomRadius, qreal rightTopRadius, qreal rightBottomRadius);
    
    QSize minimumSizeHint(void) const;
    
protected:
    void paintEvent(QPaintEvent *event);
    
private:
    dtkRegistrationBarButtonPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkRegistrationBar
// /////////////////////////////////////////////////////////////////

class dtkRegistrationBarPrivate;

class dtkRegistrationBar : public QWidget
{
    Q_OBJECT

public:
     dtkRegistrationBar(QWidget *parent = 0);
    ~dtkRegistrationBar(void);

    QSize sizeHint(void) const;

    QAbstractButton *registerButton(void);
    QAbstractButton *unregisterButton(void);

private:
    dtkRegistrationBarPrivate *d;
};

#endif
