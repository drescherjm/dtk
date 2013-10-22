/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Oct 27 14:10:37 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mar. oct. 22 09:23:57 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 150
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

    bool useGUI = false;
    QSettings settings("inria", "dtk");
    settings.beginGroup("evaluator");

    if (settings.contains("log_level"))
        dtkLogger::instance().setLevel(settings.value("log_level").toString());
    else
        dtkLogger::instance().setLevel(dtkLog::Debug);

    if (settings.contains("use_gui") && settings.value("use_gui").toString() == "true")
        useGUI =true;

    QApplication application(argc, argv, useGUI);
    application.setApplicationName("dtkComposerEvaluator");
    application.setApplicationVersion("0.0.2");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");


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
    QObject::connect(evaluator,SIGNAL(evaluationStopped()),&application, SLOT(quit()));
    QtConcurrent::run(evaluator, &dtkComposerEvaluator::run_static, false);
    application.exec();
    dtkPluginManager::instance()->uninitialize();
}
