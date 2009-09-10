/* dtkUi.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Sep  8 23:27:35 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Sep  9 09:46:28 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKUI_H
#define DTKUI_H

#include <QtGui/QWidget>

class dtkUiItem;
class dtkUiPrivate;

class dtkUi : public QWidget
{
    Q_OBJECT

public:
     dtkUi(QWidget *parent = 0);
    ~dtkUi(void);

    void append(dtkUiItem *item);

private:
    dtkUiPrivate *d;
};

#endif
