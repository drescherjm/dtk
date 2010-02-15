/* dtkNavigationBar.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb  4 18:25:17 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 20:08:19 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKNAVIGATIONBAR_H
#define DTKNAVIGATIONBAR_H

#include <QtGui>

#include "dtkGuiExport.h"

// /////////////////////////////////////////////////////////////////
// dtkNavigationBarButton
// /////////////////////////////////////////////////////////////////

class dtkNavigationBarButtonPrivate;

class DTKGUI_EXPORT dtkNavigationBarButton : public QAbstractButton
{
    Q_OBJECT
    
public:
     dtkNavigationBarButton(QWidget *parent = 0);
     dtkNavigationBarButton(const QString& text, QWidget *parent = 0);
    ~dtkNavigationBarButton(void);
    
public:
    void setRadius(qreal radius);
    void setRadius(qreal leftTopRadius, qreal leftBottomRadius, qreal rightTopRadius, qreal rightBottomRadius);
    
    QSize minimumSizeHint(void) const;
    
protected:
    void paintEvent(QPaintEvent *event);
    
private:
    dtkNavigationBarButtonPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkNavigationBar
// /////////////////////////////////////////////////////////////////

class dtkNavigationBarPrivate;

class DTKGUI_EXPORT dtkNavigationBar : public QWidget
{
    Q_OBJECT

public:
     dtkNavigationBar(QWidget *parent = 0);
    ~dtkNavigationBar(void);

    QSize sizeHint(void) const;

    QAbstractButton *backwardButton(void);
    QAbstractButton *forwardButton(void);

private:
    dtkNavigationBarPrivate *d;
};

#endif
