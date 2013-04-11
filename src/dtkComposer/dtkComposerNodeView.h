/* dtkComposerNodeView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr 24 23:27:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:57:42 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerNodeLeafView.h"

#include <QtCore>

class dtkComposerNodeViewPrivate;

class  dtkComposerNodeView : public QObject, public dtkComposerNodeLeafView
{
    Q_OBJECT

public:
     dtkComposerNodeView(void);
    ~dtkComposerNodeView(void);

public:
    void run(void);

public:
    inline bool isAbstractView(void) const {return true;} ;

    inline QString abstractViewType(void) const {return "dtkAbstractView";};

public:
    QString type(void);
    QString titleHint(void);

public:
    QString inputLabelHint(int);
    QString outputLabelHint(int);

private:
    dtkComposerNodeViewPrivate *d;
};
