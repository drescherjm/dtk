/* dtkComposerNodeView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr 24 23:27:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: jeu. sept. 20 23:46:30 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 15
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEVIEW_H
#define DTKCOMPOSERNODEVIEW_H


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

#endif
