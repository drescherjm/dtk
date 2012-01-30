/* dtkComposer_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Oct 18 13:26:40 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 24 13:15:48 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSER_P_H
#define DTKCOMPOSER_P_H

class dtkComposerEvaluator;
class dtkComposerScene;
class dtkComposerView;

#include <QtCore>

class dtkComposerPrivate : public QObject
{
    Q_OBJECT

public:
    void download(const QUrl& url);

public slots:
    void onRequestFinished(int id, bool error);

public:
    dtkComposerEvaluator *evaluator;
    dtkComposerScene *scene;
    dtkComposerView *view;

    QString fileName;
    QString tempName;

    int dwnl_id;
    int dwnl_ok;
};

#endif
