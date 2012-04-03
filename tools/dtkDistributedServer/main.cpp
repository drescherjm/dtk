/* @(#)main.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 14:41:29
 * Version: $Id$
 * Last-Updated: mar. avril  3 16:41:45 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 2
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include <dtkCore>
#include <dtkDistributed>

#include <QtCore>

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);

    if(!dtkApplicationArgumentsContain(&application, "--torque")
    && !dtkApplicationArgumentsContain(&application, "--oar")) {
        dtkDebug() << "Usage:" << argv[0] << " dtk://server:port [--oar || --torque]";
        return DTK_SUCCEED;
    }

    dtkDistributedServer server(argc, argv);
    server.run();

    int status = application.exec();

    return DTK_SUCCEED;
}

