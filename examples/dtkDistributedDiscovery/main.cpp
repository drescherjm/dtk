/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar 16 14:49:31 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 17 10:39:30 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 47
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

int main(int argc, char **argv)
{
    if(dtkApplicationArgumentsContain(argc, argv, "--help")) {
        dtkOutput() << "Usage: " << QString(argv[0]) << " (--oar | --torque) --host url";
        return 0;
    }
   
    dtkDistributedDiscoverer *discoverer = NULL;

    if(dtkApplicationArgumentsContain(argc, argv, "--oar"))
        discoverer = new dtkDistributedDiscovererOar;

    if(dtkApplicationArgumentsContain(argc, argv, "--torque"))
        discoverer = new dtkDistributedDiscovererTorque;
        
    if(!discoverer) {
        dtkCritical() << "No discovering method has been specified. See usage with --help option.";
        return 0;
    }

    QString host = dtkApplicationArgumentsValue(argc, argv, "--host");

    if(host.isEmpty()) {
        dtkCritical() << "No host has been specified. See usage with --help option.";
        return 0;
    }

    discoverer->discover(QUrl(host));

    return 0;
}
