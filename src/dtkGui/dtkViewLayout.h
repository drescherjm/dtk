/* dtkViewLayout.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:38:08 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 23 17:54:35 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 15
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

class dtkAbstractView;

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

signals:
    void focused(dtkAbstractView *view);
    
public slots:
    void clear(void);

private:
    dtkViewLayoutPrivate *d;
};

#endif
