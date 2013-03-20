/* dtkComposerFactoryView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 13:22:54 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 20 13:01:23 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERFACTORYVIEW_H
#define DTKCOMPOSERFACTORYVIEW_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

class dtkComposerFactory;
class dtkComposerFactoryViewPrivate;

class  dtkComposerFactoryView : public QWidget
{
    Q_OBJECT

public:
     dtkComposerFactoryView(QWidget *parent = 0);
    ~dtkComposerFactoryView(void);

public:
    void setFactory(dtkComposerFactory *factory);

public:
    void setDark(void);

private:
    dtkComposerFactoryViewPrivate *d;
};

#endif
