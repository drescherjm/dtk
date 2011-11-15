/* server_main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Sep 14 13:20:15 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Nov 15 15:57:01 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 323
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <dtkDistributed/dtkDistributedServer.h>

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);

    dtkDistributedServer server(argc, argv);
    server.run();

    return application.exec();
}
