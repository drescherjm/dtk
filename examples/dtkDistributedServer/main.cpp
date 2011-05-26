/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 16:02:43 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 26 12:45:46 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>
#include <QtDebug>

#include <dtkDistributed/dtkDistributedServer.h>

int main(int argc, char **argv)
{
    dtkDistributedServer server(argc, argv);

    qDebug() << server.port();
    return server.exec();
}
