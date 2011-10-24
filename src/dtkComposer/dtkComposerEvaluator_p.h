/* dtkComposerEvaluator_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Oct 24 12:54:41 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 24 13:08:16 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSEREVALUATOR_P_H
#define DTKCOMPOSEREVALUATOR_P_H

#include <QtCore/QThread>

class dtkComposerScene;

class dtkComposerEvaluatorPrivate : public QThread
{
    Q_OBJECT

public:
    void run(void);

public:
    dtkComposerScene *scene;
};

#endif
