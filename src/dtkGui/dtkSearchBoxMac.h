/* dtkSearchBoxMac.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 16 23:59:34 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Aug  6 23:47:24 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 43
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKSEARCHBOXMAC_H
#define DTKSEARCHBOXMAC_H

#include <QtGui>

#include <dtkCore/dtkGlobal.h>

#include <dtkGui/dtkSearchBox.h>

class dtkSearchBoxMacPrivate;

class dtkSearchBoxMac : public QWidget
{
    Q_OBJECT

public:
    dtkSearchBoxMac(QWidget *parent);
   ~dtkSearchBoxMac(void);

   QSize sizeHint(void) const;

   void setMenu(QMenu *menu);

signals:
   void textChanged(const QString& text, const QString& attribute);
   void textChanged(const QString& text);

public slots:
   void onTextChanged(const QString& text);

private:
   dtkSearchBoxMacPrivate *d;
};

class dtkSearchBoxAction : public QWidgetAction
{
    Q_OBJECT

public:
     dtkSearchBoxAction(const QString& text, QObject *parent = 0);
    ~dtkSearchBoxAction(void);
   
    QWidget *createWidget(QWidget *parent);

signals:
   void textChanged(const QString& text, const QString& attribute);
   void textChanged(const QString& text);

public slots:
   void setFocus(void);

private:
   dtkSearchBox *widget;
};

#endif
