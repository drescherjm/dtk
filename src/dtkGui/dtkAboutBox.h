/* dtkAboutBox.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Apr 19 12:51:22 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 19 12:55:21 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABOUTBOX_H
#define DTKABOUTBOX_H

#include <QtGui>

class dtkAboutBoxPrivate;

class dtkAboutBox : public QMessageBox
{
    Q_OBJECT

public:
     dtkAboutBox(QWidget *parent = 0);
    ~dtkAboutBox(void);

private:
    dtkAboutBoxPrivate *d;
};

#endif
