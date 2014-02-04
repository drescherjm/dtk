/* dtkComposer_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:35:09 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:04:46 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 68
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
#include "dtkComposerSupportExport.h"

class dtkComposerCompass;
class dtkComposerEvaluator;
class dtkComposerFactory;
class dtkComposerGraph;
class dtkComposerMachine;
class dtkComposerPath;
class dtkComposerScene;
class dtkComposerStack;
class dtkComposerView;
class dtkComposerWriter;
class dtkComposerReader;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerPrivate : public QObject
{
    Q_OBJECT

public:
    void download(const QUrl& url);

public slots:
    void onRequestFinished(QNetworkReply *reply);

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
    dtkComposerWriter *writer;
    dtkComposerReader *reader;

public:
    QString fileName;
    QString tempName;

    QTemporaryFile file;
    int dwnl_ok;
};

#endif
