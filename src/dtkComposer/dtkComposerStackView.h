/* dtkComposerStackView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 11:06:43 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan 31 18:08:18 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 24
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSTACKVIEW_H
#define DTKCOMPOSERSTACKVIEW_H

#include <QtGui>

class dtkComposerStack;
class dtkComposerStackViewPrivate;

class dtkComposerStackView : public QWidget
{
    Q_OBJECT

public:
     dtkComposerStackView(QWidget *parent = 0);
    ~dtkComposerStackView(void);

public:
    void setStack(dtkComposerStack *stack);

protected slots:
    void undo(void);
    void redo(void);

private:
    dtkComposerStackViewPrivate *d;
};

#endif
