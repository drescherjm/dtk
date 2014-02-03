/* dtkAboutBox.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Apr 19 12:51:22 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun  1 20:59:13 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABOUTBOX_H
#define DTKABOUTBOX_H

#include "dtkGuiExport.h"

#include <QtGui>

class dtkAboutBoxPrivate;

class DTKGUI_EXPORT dtkAboutBox : public QMessageBox
{
    Q_OBJECT

public:
     dtkAboutBox(QWidget *parent = 0);
    ~dtkAboutBox(void);

private:
    dtkAboutBoxPrivate *d;
};

#endif
