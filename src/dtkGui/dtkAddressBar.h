/* dtkAddressBar.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb  4 11:01:31 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  5 15:51:20 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 23
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKADDRESSBAR_H
#define DTKADDRESSBAR_H

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkAddressBarButton
// /////////////////////////////////////////////////////////////////

class dtkAddressBarButtonPrivate;

class dtkAddressBarButton : public QAbstractButton
{
    Q_OBJECT
    
public:
     dtkAddressBarButton(QWidget *parent = 0);
     dtkAddressBarButton(const QString& text, QWidget *parent = 0);
    ~dtkAddressBarButton(void);
    
public:
    void setRadius(qreal radius);
    void setRadius(qreal leftTopRadius, qreal leftBottomRadius, qreal rightTopRadius, qreal rightBottomRadius);
    
    QSize minimumSizeHint(void) const;
    
protected:
    void paintEvent(QPaintEvent *event);
    
private:
    dtkAddressBarButtonPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkAddressBar
// /////////////////////////////////////////////////////////////////

class dtkAddressBarPrivate;

class dtkAddressBar : public QWidget
{
    Q_OBJECT

public:
     dtkAddressBar(QWidget *parent = 0);
    ~dtkAddressBar(void);

    QSize       sizeHint(void) const;    
    QSizePolicy sizePolicy(void) const;

signals:
    void addressEntered(const QUrl& url);

public slots:
    void setText(const QString& text);

protected slots:
    void onReturnPressed(void);

private:
    dtkAddressBarPrivate *d;
};

#endif
