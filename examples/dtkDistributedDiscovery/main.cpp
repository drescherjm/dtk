/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar 16 14:49:31 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Mar 27 13:33:59 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 58
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>

#include <dtkDistributed/dtkDistributedDiscoverer.h>
#include <dtkDistributed/dtkDistributedDiscovererOar.h>
#include <dtkDistributed/dtkDistributedDiscovererTorque.h>
#include <dtkDistributed/dtkDistributor.h>

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    dtkDistributor *distributor = new dtkDistributor;
    distributor->resize(800, 480);
    distributor->show();

    return application.exec();
}
