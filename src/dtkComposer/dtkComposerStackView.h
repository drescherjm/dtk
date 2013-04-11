/* dtkComposerStackView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 11:06:43 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:36:50 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 30
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include <QtGui>

class dtkComposerStack;
class dtkComposerStackViewPrivate;

class  dtkComposerStackView : public QWidget
{
    Q_OBJECT

public:
     dtkComposerStackView(QWidget *parent = 0);
    ~dtkComposerStackView(void);

public:
    void setStack(dtkComposerStack *stack);

private:
    dtkComposerStackViewPrivate *d;
};

