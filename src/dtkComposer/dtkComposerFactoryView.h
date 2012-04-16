/* dtkComposerFactoryView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 13:22:54 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Apr 16 12:19:00 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERFACTORYVIEW_H
#define DTKCOMPOSERFACTORYVIEW_H

#include "dtkComposerExport.h"

#include <QtCore>
#include <QtGui>

class dtkComposerFactory;
class dtkComposerFactoryViewPrivate;

class DTKCOMPOSER_EXPORT dtkComposerFactoryView : public QWidget
{
    Q_OBJECT

public:
     dtkComposerFactoryView(QWidget *parent = 0);
    ~dtkComposerFactoryView(void);

public:
    void setFactory(dtkComposerFactory *factory);

private:
    dtkComposerFactoryViewPrivate *d;
};

#endif
