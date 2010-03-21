/* dtkDistributedDiscovererTorque.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Mar 17 09:55:42 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar 21 23:47:41 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 65
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedDiscoverer_p.h"
#include "dtkDistributedDiscovererTorque.h"
#include "dtkDistributedNode.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>

#include <dtkSsh/dtkSshController.h>

#include <QtXml>

void dtkDistributedDiscovererTorque::discover(const QUrl& url)
{
    dtkDebug() << "Opening ssh connection towards " << url.toString();

    QString result;

    dtkSshController::instance()->createConnection(url);
    dtkSshController::instance()->execute("pbsnodes -x", result);

    result = result.split("\n").first(); // Figure this out !

    QDomDocument document; QString error;

    if(document.setContent(result, false, &error))
        dtkDebug() << "Successfully retrieved xml output out of " << url.toString() << "torque setup";
    else
        dtkDebug() << "Error retrieving xml output out of " << url.toString() << error;

    qDebug() << "- " << DTK_COLOR_FG_RED << document.toString() << DTK_NO_COLOR;

    QDomNodeList nodes = document.elementsByTagName("Node");

    for(int i = 0; i < nodes.count(); i++) {

        QString name  = nodes.item(i).firstChildElement("name").text().simplified();
        QString state = nodes.item(i).firstChildElement("state").text().simplified();
        QStringList properties = nodes.item(i).firstChildElement("properties").text().simplified().split(",");

        dtkDistributedNode *node = new dtkDistributedNode;
        node->setName(name);

        if(state == "free")
            node->setState(dtkDistributedNode::Free);
       
        if(state == "job-exclusive")
            node->setState(dtkDistributedNode::JobExclusive);

        if(state == "down")
            node->setState(dtkDistributedNode::Down);
        
        if(state == "offline")
            node->setState(dtkDistributedNode::Offline);

        

        d->nodes << node;
    }
}

// <Node>
//  <name>nef001.inria.fr</name>
//  <state>job-exclusive</state>
//  <np>2</np>
//  <properties>nef,opteron,singlecore,ibm,ghz200</properties>
//  <ntype>cluster</ntype>
//  <jobs>0/1799848.nef.inria.fr, 1/1799848.nef.inria.fr</jobs>
//  <status>opsys=linux,uname=Linux nef001 2.6.27.41-170.2.117.fc10.x86_64 #1 SMP Thu Dec 10 10:36:29 EST2009 x86_64,sessions=5576,nsessions=1,nusers=1,idletime=176837,totmem=5966352kb,availmem=4691004kb,physmem=2059888kb,ncpus=2,loadave=2.06,netload=1795010938166,state=free,jobs=1799848.nef.inria.fr,rectime=1269209517</status>
// </Node>
