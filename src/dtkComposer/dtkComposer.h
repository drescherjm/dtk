/* dtkComposer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Sep  4 10:12:32 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  7 13:43:48 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSER_H
#define DTKCOMPOSER_H

#include <QtGui/QWidget>

class dtkComposerPrivate;

class dtkComposer : public QWidget
{
    Q_OBJECT

public:
     dtkComposer(QWidget *parent = 0);
    ~dtkComposer(void);

private:
    dtkComposerPrivate *d;
};

#endif
