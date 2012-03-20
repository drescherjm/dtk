/* dtkSwitch.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb 29 23:53:52 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar 20 13:43:12 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKSWITCH_H
#define DTKSWITCH_H

#include <QtGui>
#include <QtDeclarative>

class dtkSwitchPrivate;

class dtkSwitch : public QDeclarativeView
{
    Q_OBJECT

public:
     dtkSwitch(QWidget *parent = 0);
    ~dtkSwitch(void);

signals:
     void toggled(bool);

public:
     Q_INVOKABLE QString foreground(void);
     Q_INVOKABLE QString background(void);

public:
     Q_INVOKABLE QString leftLabel(void);
     Q_INVOKABLE QString rightLabel(void);

public slots:
     void toggle(void);

public slots:
     void setForeground(const QString& pixmap);
     void setBackground(const QString& pixmap);

public slots:
     void setLeftLabel(const QString& label);
     void setRightLabel(const QString& label);

private:
     dtkSwitchPrivate *d;
};

#endif // DTKSWITCH_H
