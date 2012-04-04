/* @(#)main.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 14:41:29
 * Version: $Id$
 * Last-Updated: Wed Apr  4 11:21:44 2012 (+0200)
 *           By: tkloczko
 *     Update #: 3
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include <dtkCore>
#include <dtkDistributed>

#include <dtkLog/dtkLog.h>

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

