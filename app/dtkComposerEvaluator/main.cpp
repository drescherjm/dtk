/* main.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2014 - Nicolas Niclausse, Inria.
 * Created: 2014/10/28 12:45:34
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */




#include <dtkDistributed>
#include <dtkComposer>
#include <dtkCore>

#include <dtkCoreSupport/dtkPluginManager.h>
#include <dtkCoreSupport/dtkAbstractProcessFactory.h>

#include <QtConcurrent>

int main(int argc, char **argv)
{
    dtkDistributedApplication *application = dtkDistributed::create(argc, argv);

    application->setApplicationName("dtkComposerEvaluator");
    application->setApplicationVersion("1.0.0");
    application->setOrganizationName("inria");
    application->setOrganizationDomain("fr");
    bool no_gui = dtkDistributed::app()->noGui();

    QCommandLineParser *parser = application->parser();
    parser->setApplicationDescription("DTK composer evaluator. Run the given compostion (XML file).");
    QCommandLineOption pgOption("pg", "enable profiling");
    parser->addOption(pgOption);
    application->initialize();

    QStringList args = parser->positionalArguments();

    if (args.isEmpty()) {
        qDebug() << "Usage: " << argv[0] << "--spawn | [-pg] <composition> ";
        return 1;
    }

    // /////////////////////////////////////////////////////////////////
    // Old Plugin manager initialization
    // /////////////////////////////////////////////////////////////////

    QSettings *main_settings = application->settings();
    main_settings->beginGroup("plugins");

    if (main_settings->contains("path")) {
        dtkPluginManager::instance()->setPath(main_settings->value("path").toString());
    }

    if (parser->isSet("verbose")) {
        dtkPluginManager::instance()->setVerboseLoading(true);
    }

    main_settings->endGroup();
    dtkPluginManager::instance()->initialize();

    dtkComposerFactory *factory = new dtkComposerFactory;

//     if (args[1] == "--spawn") {

//         dtkComposerEvaluatorProcess p;
// //        p.setInternalCommunicator(comm);
//         p.setParentCommunicator(policy.communicator());
//         p.setFactory(factory);
//         p.setApplication("dtkComposerEvaluator");

//         int value;
//         do  { value = p.exec(); } while (value  == 0);

//         return value;
//     }

    dtkComposerScene *scene = new dtkComposerScene;
    dtkComposerStack *stack = new dtkComposerStack;
    dtkComposerGraph *graph = new dtkComposerGraph;
    dtkComposerEvaluator *evaluator = new dtkComposerEvaluator;;

    scene->setFactory(factory);
    scene->setStack(stack);
    scene->setGraph(graph);

    evaluator->setGraph(graph);

    dtkComposerReader *reader;
    reader = new dtkComposerReader;
    reader->setFactory(factory);
    reader->setScene(scene);
    reader->setGraph(graph);

    if (parser->isSet(pgOption)) {
        evaluator->setProfiling(true);
    }
    if (!reader->read(args.first())) {
        dtkError() << "read failure for " << args.first();
        return 1;
    }
    if (no_gui) {
        evaluator->run_static();
    } else {
        QObject::connect(evaluator,SIGNAL(evaluationStopped()),qApp, SLOT(quit()));
        QtConcurrent::run(evaluator, &dtkComposerEvaluator::run_static, false);
        qApp->exec();
    }
    dtkPluginManager::instance()->uninitialize();
}

