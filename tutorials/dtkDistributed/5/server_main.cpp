/* server_main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Sep 14 13:20:15 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Nov 23 12:06:55 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 328
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>

#include <dtkCore>
#include <dtkDistributed>

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
