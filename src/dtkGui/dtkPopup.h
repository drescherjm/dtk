/* dtkPopup.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Mar 18 15:38:29 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Mar 18 15:45:21 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 17
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

private:
    dtkPopupPrivate *d;
};

#endif
