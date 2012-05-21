/* dtkViewLayout.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:38:08 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 21 15:54:05 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVIEWLAYOUT_H
#define DTKVIEWLAYOUT_H

#include "dtkGuiExport.h"

#include <QtGui>

class dtkViewLayoutItem;
class dtkViewLayoutPrivate;

class DTKGUI_EXPORT dtkViewLayout : public QFrame
{
    Q_OBJECT

public:
     dtkViewLayout(QWidget *parent = 0);
    ~dtkViewLayout(void);

public:
    dtkViewLayoutItem *root(void);
    dtkViewLayoutItem *current(void);

public:
    void setCurrent(dtkViewLayoutItem *item);

private:
    dtkViewLayoutPrivate *d;
};

#endif
