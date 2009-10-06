/* dtkComposerEvaluator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Sep 11 22:51:47 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Sep 13 16:15:58 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 16
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

class dtkComposerNode;
class dtkComposerScene;
class dtkComposerEvaluatorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerEvaluator : public QObject
{
    Q_OBJECT

public:
     dtkComposerEvaluator(void);
    ~dtkComposerEvaluator(void);

    void run(void);
    void stop(void);

    void setScene(dtkComposerScene *scene);

protected slots:
    void evaluate(dtkComposerNode *node);

private:
    dtkComposerEvaluatorPrivate *d;
};

#endif
