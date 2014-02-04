/* dtkComposerStackView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 11:06:43 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Apr 16 12:18:36 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 29
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSTACKVIEW_H
#define DTKCOMPOSERSTACKVIEW_H

#include "dtkComposerSupportExport.h"

#include <QtWidgets>

class dtkComposerStack;
class dtkComposerStackViewPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerStackView : public QWidget
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

#endif
