/* dtkComposerEvaluator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Oct 24 12:51:53 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 24 13:08:37 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 13
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
class dtkComposerScene;

class DTKCOMPOSER_EXPORT dtkComposerEvaluator : public QObject
{
    Q_OBJECT

public:
     dtkComposerEvaluator(void);
    ~dtkComposerEvaluator(void);

    void setScene(dtkComposerScene *scene);

public slots:
    void start(void);
    void stop(void);

private:
    dtkComposerEvaluatorPrivate *d;
};

#endif
