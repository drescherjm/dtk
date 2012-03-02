/* dtkComposerEvaluator.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:30:36 2012 (+0100)
 * Version: $Id$
 * Last-Updated: ven. mars  2 18:12:21 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSEREVALUATOR_H
#define DTKCOMPOSEREVALUATOR_H

#include "dtkComposerExport.h"

#include <QtCore/QObject>

class dtkComposerGraph;
class dtkComposerEvaluatorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerEvaluator : public QObject
{
    Q_OBJECT

public:
     dtkComposerEvaluator(QObject *parent = 0);
    ~dtkComposerEvaluator(void);

signals:
    void started();
    void stopped();

public:
    void setGraph(dtkComposerGraph *graph);

public:
    void run(void);

private:
    dtkComposerEvaluatorPrivate *d;
};

#endif
