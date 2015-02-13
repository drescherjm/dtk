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

#include <QtConcurrent>

int main(int argc, char **argv)
{


    bool useGUI = false;

    QApplication application(argc, argv, useGUI);
    application.setApplicationName("dtkComposerEvaluator");
    application.setApplicationVersion("1.0.0");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");

    // plugins
    dtkDistributedSettings settings;
    settings.beginGroup("communicator");
    qDebug() << "initialize plugin manager "<< settings.value("plugins").toString();
    dtkDistributed::communicator::pluginManager().initialize(settings.value("plugins").toString());
    qDebug() << "initialization done ";
    settings.endGroup();

    qDebug() << dtkDistributed::communicator::pluginManager().plugins();
    qDebug() << dtkDistributed::communicator::pluginFactory().keys();

    QStringList args = QCoreApplication::arguments();
    if(args.count() < 2) {
        qDebug() << "argv" << args;
        qDebug() << "Usage: " << argv[0] << "--spawn | [-pg] <composition> ";
        return 0;
    }

    dtkComposerNodeFactory *factory = new dtkComposerNodeFactory;

    if (args[1] == "--spawn") {

        // FIXME: don't hardcode plugin
        dtkDistributedPolicy policy;
        //FIXME: don't use manager
        // dtkDistributedWorkerManager manager;
        // policy.setType("mpi3");
        // manager.setPolicy(&policy);

        dtkComposerEvaluatorProcess p;

        QStringList hosts;
        // dtkDistributedCommunicator *comm = manager.spawn();
        dtkDistributedCommunicator *comm ;
        //manager.spawn();

        p.setInternalCommunicator(comm);
        p.setParentCommunicator(policy.communicator());
        p.setFactory(factory);
        p.setApplication("dtkComposerEvaluator");

        int value;
        do  { value = p.exec(); } while (value  == 0);

        return value;
    }

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

    int index= 1;

    if (args[1] == "-pg") {
        index = 2;
        evaluator->setProfiling(true);
    }


    if (!reader->read(argv[index])) {
        qDebug() << "read failure for " << argv[index];
        return 1;
    } else {

        QObject::connect(evaluator,SIGNAL(evaluationStopped()),&application, SLOT(quit()));
        QtConcurrent::run(evaluator, &dtkComposerEvaluator::run_static, false);
        application.exec();
        // dtkPluginManager::instance()->uninitialize();
    }
}

