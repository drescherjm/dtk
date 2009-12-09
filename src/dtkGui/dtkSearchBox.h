/* dtkSearchBox.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Oct  7 08:14:03 2008 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Dec  9 10:09:12 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 62
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

#include <dtkGui/dtkGuiExport.h>

class dtkSearchBoxPrivate;

class DTKGUI_EXPORT dtkSearchBox : public QWidget
{
    Q_OBJECT

public:
    dtkSearchBox(QWidget *parent = 0);
   ~dtkSearchBox(void);

   QString text(void) const;

signals:
   void search(const QString& text);
   void textChanged(const QString& text);

public slots:
    void setText(const QString& text);

private slots:
   void onButtonClicked(void);
   void onEnterPressed(void);

private:
   dtkSearchBoxPrivate *d;
};

#endif
