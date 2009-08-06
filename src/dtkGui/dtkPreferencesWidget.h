/* dtkPreferencesWidget.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Aug  6 09:48:31 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Aug  6 10:34:12 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 23
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPREFERENCESWIDGET_H
#define DTKPREFERENCESWIDGET_H

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkPreferencesPage
// /////////////////////////////////////////////////////////////////

class dtkPreferencesPage : public QWidget
{
    Q_OBJECT

public:
             dtkPreferencesPage(QWidget *parent = 0) : QWidget(parent) {}
    virtual ~dtkPreferencesPage(void) {}

signals:
    virtual void accepted(void) = 0;
    virtual void rejected(void) = 0;
};

// /////////////////////////////////////////////////////////////////
// dtkPreferencesWidget
// /////////////////////////////////////////////////////////////////

class dtkPreferencesWidgetPrivate;

class dtkPreferencesWidget : public QMainWindow
{
    Q_OBJECT

public:
     dtkPreferencesWidget(QWidget *parent = 0);
    ~dtkPreferencesWidget(void);

    void addPage(const QString& title, dtkPreferencesPage *page);
    void addPage(const QString& title, dtkPreferencesPage *page, const QIcon& icon);

protected:
    void showEvent(QShowEvent *event);
    
private slots:
    void onActionTriggered(void);
    
private:
    dtkPreferencesWidgetPrivate *d;
};

#endif
