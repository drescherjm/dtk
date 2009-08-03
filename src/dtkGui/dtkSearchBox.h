/* dtkSearchBox.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Oct  7 08:14:03 2008 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Aug  2 14:59:30 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 60
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKSEARCHBOX_H
#define DTKSEARCHBOX_H

#include <QtGui>

#include <dtkCore/dtkGlobal.h>

#include <dtkGui/dtkGuiExport.h>

class dtkSearchBoxPrivate;

class DTKGUI_EXPORT dtkSearchBox : public QWidget
{
    Q_OBJECT

public:
    dtkSearchBox(QWidget *parent = 0);
   ~dtkSearchBox(void);

   void setMenu(QMenu *menu);

signals:
   void textChanged(const QString& text, const QString& attribute);
   void textChanged(const QString& text);

public slots:
   void setFocus(void);

private:
   dtkSearchBoxPrivate *d;
};

#endif
