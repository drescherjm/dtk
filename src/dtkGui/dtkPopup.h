/* dtkPopup.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Mar 18 15:38:29 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Sep  5 11:05:41 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPOPUP_H
#define DTKPOPUP_H

#include <QtGui/QFrame>

class dtkPopupPrivate;

class dtkPopup : public QFrame
{
    Q_OBJECT

public:
    dtkPopup(QWidget *parent = 0);

    void setWidget(QWidget *widget, bool own = true);

    QWidget *widget(void) const;
    bool isOwned(void) const;

public slots:
    void show(QPoint coord);

#if defined(Q_WS_MAC)
protected:
    bool macEvent(EventHandlerCallRef caller, EventRef event) {
        Q_UNUSED(caller);
        Q_UNUSED(event);
        return true;
    }
#endif

private:
    dtkPopupPrivate *d;
};

#endif
