/* dtkComposerWidget_p.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:35:09 2012 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <QtCore>
#include <QtNetwork>
#include "dtkComposerExport.h"

class dtkComposerCompass;
class dtkComposerEvaluator;
class dtkComposerNodeFactory;
class dtkComposerGraph;
class dtkComposerMachine;
class dtkComposerPath;
class dtkComposerScene;
class dtkComposerStack;
class dtkComposerView;
class dtkComposerWriter;
class dtkComposerReader;

class DTKCOMPOSER_EXPORT dtkComposerWidgetPrivate : public QObject
{
    Q_OBJECT

public:
    void download(const QUrl& url);

public slots:
    void onRequestFinished(QNetworkReply *reply);

public:
    dtkComposerCompass *compass;
    dtkComposerEvaluator *evaluator;
    dtkComposerNodeFactory *factory;
    dtkComposerGraph *graph;
    dtkComposerMachine *machine;
    dtkComposerScene *scene;
    dtkComposerStack *stack;
    dtkComposerView *view;
    dtkComposerPath *path;
    dtkComposerWriter *writer;
    dtkComposerReader *reader;

public:
    QString fileName;
    QString tempName;

    QTemporaryFile file;
    int dwnl_ok;
};
