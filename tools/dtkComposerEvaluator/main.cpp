/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Oct 27 14:10:37 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Oct 27 14:34:50 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 38
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore>
#include <dtkComposer>

#include <QtCore>
#include <QtGui>

int main(int argc, char **argv)
{
    if(argc != 2) {
        qDebug() << "Usage: ./" << argv[1] << " <composition>";
        return 0;
    }

    QApplication application(argc, argv);
    application.setApplicationName("dtkComposerEvaluator");
    application.setApplicationVersion("0.0.1");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");

    dtkPluginManager::instance()->initialize();

    dtkComposerScene scene;

    dtkComposerReader reader(&scene);
    reader.read(argv[1]);

    dtkComposerEvaluator evaluator(&scene);

    QObject::connect(&evaluator, SIGNAL(evaluationStopped()), &application, SLOT(quit()));
    
    evaluator.start();

    int status = application.exec();

    dtkPluginManager::instance()->uninitialize();

    return status;
}
