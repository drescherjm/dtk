/* dtkSearchBar.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb  4 11:01:02 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb  7 16:00:21 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKSEARCHBAR_H
#define DTKSEARCHBAR_H

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkSearchBarButton
// /////////////////////////////////////////////////////////////////

class dtkSearchBarButtonPrivate;

class dtkSearchBarButton : public QAbstractButton
{
    Q_OBJECT
    
public:
     dtkSearchBarButton(QWidget *parent = 0);
     dtkSearchBarButton(const QString& text, QWidget *parent = 0);
    ~dtkSearchBarButton(void);
    
public:
    void setRadius(qreal radius);
    void setRadius(qreal leftTopRadius, qreal leftBottomRadius, qreal rightTopRadius, qreal rightBottomRadius);
    
    QSize minimumSizeHint(void) const;
    
protected:
    void paintEvent(QPaintEvent *event);
    
private:
    dtkSearchBarButtonPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkSearchBar
// /////////////////////////////////////////////////////////////////

class dtkSearchBarPrivate;

class dtkSearchBar : public QWidget
{
    Q_OBJECT

public:
     dtkSearchBar(QWidget *parent = 0);
    ~dtkSearchBar(void);

    QSize       sizeHint(void) const;    
    QSizePolicy sizePolicy(void) const;

    QString text(void) const;

signals:
    void textChanged(QString);
    void returnPressed();

protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

private:
    dtkSearchBarPrivate *d;
};

#endif
