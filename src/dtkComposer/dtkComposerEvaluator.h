/* dtkComposerEvaluator.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:30:36 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 11:34:07 2012 (+0100)
 *           By: tkloczko
 *     Update #: 1
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

class dtkComposerEvaluatorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerEvaluator : public QObject
{
    Q_OBJECT

public:
     dtkComposerEvaluator(QObject *parent = 0);
    ~dtkComposerEvaluator(void);

private:
    dtkComposerEvaluatorPrivate *d;
};

#endif
