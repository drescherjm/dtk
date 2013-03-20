/* dtkComposer_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:35:09 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 20 14:26:02 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 66
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSER_P_H
#define DTKCOMPOSER_P_H

#include <QtCore>
#include <QtNetwork>

class dtkComposerCompass;
class dtkComposerEvaluator;
class dtkComposerFactory;
class dtkComposerGraph;
class dtkComposerMachine;
class dtkComposerPath;
class dtkComposerScene;
class dtkComposerStack;
class dtkComposerView;

class dtkComposerPrivate : public QObject
{
    Q_OBJECT

public:
    void download(const QUrl& url);

public slots:
    void onRequestFinished(QNetworkReply *);

public:
    dtkComposerCompass *compass;
    dtkComposerEvaluator *evaluator;
    dtkComposerFactory *factory;
    dtkComposerGraph *graph;
    dtkComposerMachine *machine;
    dtkComposerScene *scene;
    dtkComposerStack *stack;
    dtkComposerView *view;
    dtkComposerPath *path;

public:
    QString fileName;
    QString tempName;

    int dwnl_id;
    int dwnl_ok;
};

#endif
