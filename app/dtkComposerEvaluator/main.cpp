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
#include <dtkWidgets>

#include <QtConcurrent>

int main(int argc, char **argv)
{
    dtkDistributedGuiApplication *application = dtkDistributedGuiApplication::create(argc, argv);

    application->setApplicationName("dtkComposerEvaluator");
    application->setApplicationVersion("1.0.0");
    application->setOrganizationName("inria");
    application->setOrganizationDomain("fr");
    bool no_gui = application->noGui();

    QCommandLineParser *parser = application->parser();
    parser->setApplicationDescription("DTK composer evaluator. Run the given compostion (XML file).");

    // /////////////////////////////////////////////////////////////////
    // Arguments & Options
    // /////////////////////////////////////////////////////////////////

    QCommandLineOption pgOption("pg", "enable profiling");
    parser->addOption(pgOption);

    QCommandLineOption slaveOption("slave", "run as a dtk distributed slave instance");
    parser->addOption(slaveOption);

    QCommandLineOption serverOption("server", "DTK distributed server URL", "URL");
    parser->addOption(serverOption);

    application->initialize();

    QStringList args = parser->positionalArguments();

    if (args.isEmpty() && !parser->isSet(slaveOption)) {
        qDebug() << "Usage: " << argv[0] << "--spawn | [-pg] <composition> ";
        return 1;
    }

    // /////////////////////////////////////////////////////////////////
    // Old Plugin manager initialization
    // /////////////////////////////////////////////////////////////////

    // QSettings *main_settings = application->settings();
    // main_settings->beginGroup("plugins");

    // if (main_settings->contains("path")) {
    //     dtkPluginManager::instance()->setPath(main_settings->value("path").toString());
    // }

    // if (parser->isSet("verbose")) {
    //     dtkPluginManager::instance()->setVerboseLoading(true);
    // }

    // main_settings->endGroup();
    // dtkPluginManager::instance()->initialize();

    dtkComposerNodeFactory *factory = &(dtkComposer::node::factory());

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

    if (parser->isSet(slaveOption)) {
        dtkComposerEvaluatorSlave *slave = new dtkComposerEvaluatorSlave;
        if (!parser->isSet(serverOption)) {
            qCritical() << "Error: no server set when running as slave! Use --server <url> " ;
            return 1;
        }
        slave->setServer(parser->value(serverOption));
        slave->setFactory(factory);

        application->spawn();
        do  { application->exec(slave); } while (slave->status()  == 0);
        application->unspawn();

    } else {
        dtkComposerGraph *graph = new dtkComposerGraph;
        dtkComposerEvaluator *evaluator = new dtkComposerEvaluator;;

        evaluator->setGraph(graph);

        dtkComposerReaderNoScene *reader;
        reader = new dtkComposerReaderNoScene;
        reader->setFactory(factory);
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
    }
}

