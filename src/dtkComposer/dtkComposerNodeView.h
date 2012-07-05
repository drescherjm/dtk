/* dtkComposerNodeView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr 24 23:27:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. juil.  3 18:59:35 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEVIEW_H
#define DTKCOMPOSERNODEVIEW_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeafView.h"

#include <QtCore>

class dtkComposerNodeViewPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeView : public QObject, public dtkComposerNodeLeafView
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

signals:
    void runned(void);

protected slots:
    void onRun(void);

private:
    dtkComposerNodeViewPrivate *d;
};

#endif
