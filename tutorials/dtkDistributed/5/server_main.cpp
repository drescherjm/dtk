/* server_main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Sep 14 13:20:15 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Sep 20 16:16:40 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 311
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkDistributed/dtkDistributedServer.h>

int main(int argc, char **argv)
{
    dtkDistributedServer server(argc, argv);

    return server.exec();
}
