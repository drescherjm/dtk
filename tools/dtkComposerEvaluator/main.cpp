/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Oct 27 14:10:37 2011 (+0200)
 * Version: $Id$
 * Last-Updated: ven. avril 13 13:59:36 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 116
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkLog/dtkLog.h>

#include <dtkCore>
#include "dtkComposer/dtkComposerEvaluator.h"
#include "dtkComposer/dtkComposerFactory.h"
#include "dtkComposer/dtkComposerGraph.h"
#include "dtkComposer/dtkComposerReader.h"
#include "dtkComposer/dtkComposerScene.h"
#include "dtkComposer/dtkComposerStack.h"

#include <QtCore>
#include <QtGui>

int main(int argc, char **argv)
{
    if(argc != 2) {
        qDebug() << "Usage: " << argv[0] << " <composition>";
        return 0;
    }

    QApplication application(argc, argv, false);
    application.setApplicationName("dtkComposerEvaluator");
    application.setApplicationVersion("0.0.2");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");

    dtkLogger::instance().setLevel(dtkLog::Info);
    dtkLogger::instance().attachFile(dtkLogPath(&application));

    dtkPluginManager::instance()->initialize();

    dtkComposerScene *scene;
    dtkComposerStack *stack;
    dtkComposerGraph *graph;
    dtkComposerFactory *factory;
    dtkComposerEvaluator *evaluator;

    factory = new dtkComposerFactory;
    graph = new dtkComposerGraph;
    stack = new dtkComposerStack;
    scene = new dtkComposerScene;
    evaluator = new dtkComposerEvaluator;

    scene->setFactory(factory);
    scene->setStack(stack);
    scene->setGraph(graph);

    evaluator->setGraph(graph);

    dtkComposerReader *reader;
    reader = new dtkComposerReader;
    reader->setFactory(factory);
    reader->setScene(scene);
    reader->setGraph(graph);
    if (!reader->read(argv[1])) {
        dtkError() << "read failure for " << argv[1];
        return 1;
    }

    evaluator->run();

    dtkPluginManager::instance()->uninitialize();
}
