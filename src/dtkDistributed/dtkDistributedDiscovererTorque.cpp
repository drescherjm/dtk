/* dtkDistributedDiscovererTorque.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Mar 17 09:55:42 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 25 11:34:41 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 103
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedCore.h"
#include "dtkDistributedCpu.h"
#include "dtkDistributedGpu.h"
#include "dtkDistributedDiscoverer_p.h"
#include "dtkDistributedDiscovererTorque.h"
#include "dtkDistributedNode.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>

#include <QtXml>

void dtkDistributedDiscovererTorque::discover(const QUrl& url)
{
    static bool discovered = false;

    if(discovered)
        return;

    dtkDebug() << "Opening ssh connection towards " << url.toString();

    // dtkSshController::instance()->createConnection(url);
    // dtkSshController::instance()->execute("pbsnodes -x", result);

    QProcess stat; stat.start("ssh", QStringList() << "nef.inria.fr" << "pbsnodes -x");

    if (!stat.waitForStarted()) {
        dtkCritical() << "Unable to launch ssh command";
        return;
    }

    if (!stat.waitForFinished()) {
        dtkCritical() << "Unable to completed ssh command";
        return;
    }
    
    QString result = stat.readAll();

    // result = result.split("\n").first(); // Figure this out !

    QDomDocument document; QString error;

    if(document.setContent(result, false, &error))
        dtkDebug() << "Successfully retrieved xml output out of " << url.toString() << "torque setup";
    else
        dtkDebug() << "Error retrieving xml output out of " << url.toString() << error;

    qDebug() << "- " << DTK_COLOR_FG_RED << document.toString() << DTK_NO_COLOR;

    QDomNodeList nodes = document.elementsByTagName("Node");

    for(int i = 0; i < nodes.count(); i++) {

        int np = nodes.item(i).firstChildElement("np").text().simplified().toInt();
        QString name  = nodes.item(i).firstChildElement("name").text().simplified();
        QString state = nodes.item(i).firstChildElement("state").text().simplified();
        QString status = nodes.item(i).firstChildElement("status").text().simplified();
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

        if(properties.contains("dell"))
            node->setBrand(dtkDistributedNode::Dell);

        if(properties.contains("hp"))
            node->setBrand(dtkDistributedNode::Hp);

        if(properties.contains("ibm"))
            node->setBrand(dtkDistributedNode::Ibm);

        if(properties.contains("myrinet"))
            node->setNetwork(dtkDistributedNode::Myrinet10G);
        else
            node->setNetwork(dtkDistributedNode::Ethernet1G);

        if(properties.contains("gpu")) for(int i = 0; i < np; i++) {

            dtkDistributedGpu *gpu = new dtkDistributedGpu(node);

            if(status.contains("x86_64"))
                gpu->setArchitecture(dtkDistributedGpu::x86_64);
            else
                gpu->setArchitecture(dtkDistributedGpu::x86);

            if(properties.contains("opteron"))
                gpu->setModel(dtkDistributedGpu::Opteron);

            if(properties.contains("xeon"))
                gpu->setModel(dtkDistributedGpu::Xeon);

            int nc = 0;
            
            if(properties.contains("singlecore"))
                nc = 1;
            else if(properties.contains("dualcore"))
                nc = 2;
            else if(properties.contains("quadcore"))
                nc = 4;
            
            for(int i = 0; i < nc; i++)
                *gpu << new dtkDistributedCore(gpu);

            *node << gpu;
        }

        else for(int i = 0; i < np; i++) {

            dtkDistributedCpu *cpu = new dtkDistributedCpu(node);

            if(status.contains("x86_64"))
                cpu->setArchitecture(dtkDistributedCpu::x86_64);
            else
                cpu->setArchitecture(dtkDistributedCpu::x86);

            if(properties.contains("opteron"))
                cpu->setModel(dtkDistributedCpu::Opteron);

            if(properties.contains("xeon"))
                cpu->setModel(dtkDistributedCpu::Xeon);

            int nc = 0;
            
            if(properties.contains("singlecore"))
                nc = 1;
            else if(properties.contains("dualcore"))
                nc = 2;
            else if(properties.contains("quadcore"))
                nc = 4;
            
            for(int i = 0; i < nc; i++)
                *cpu << new dtkDistributedCore(cpu);

            *node << cpu;
        }

        d->nodes << node;
    }

    discovered = true;
}
