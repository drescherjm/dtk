/* dtkPreferencesWidget.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Aug  6 09:48:31 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  5 10:51:37 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 29
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

#if defined(Q_WS_MAC)
protected:
    bool macEvent(EventHandlerCallRef caller, EventRef event) {
        Q_UNUSED(caller);
        Q_UNUSED(event);
        return true;
    }
#endif
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

#if defined(Q_WS_MAC)
    bool macEvent(EventHandlerCallRef caller, EventRef event) {
        Q_UNUSED(caller);
        Q_UNUSED(event);
        return true;
    }
#endif

private slots:
    void onActionTriggered(void);
    
private:
    dtkPreferencesWidgetPrivate *d;
};

#endif
