/* dtkPreferencesWidget.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Aug  6 09:48:31 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Oct  6 14:40:39 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 24
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPREFERENCESWIDGET_H
#define DTKPREFERENCESWIDGET_H

#include "dtkGuiExport.h"

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkPreferencesPage
// /////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT dtkPreferencesPage : public QWidget
{
    Q_OBJECT

public:
             dtkPreferencesPage(QWidget *parent = 0) : QWidget(parent) {}
    virtual ~dtkPreferencesPage(void) {}

signals:
    void accepted(void);
    void rejected(void);
};

// /////////////////////////////////////////////////////////////////
// dtkPreferencesWidget
// /////////////////////////////////////////////////////////////////

class dtkPreferencesWidgetPrivate;

class DTKGUI_EXPORT dtkPreferencesWidget : public QMainWindow
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
