/* dtkDistributedDiscovererTorque.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Mar 17 09:55:42 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 31 21:20:37 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 120
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
    QProcess stat; stat.start("ssh", QStringList() << url.toString() << "pbsnodes -x");

    if (!stat.waitForStarted()) {
        dtkCritical() << "Unable to launch ssh command";
        return;
    }

    if (!stat.waitForFinished()) {
        dtkCritical() << "Unable to completed ssh command";
        return;
    }
    
    QString result = stat.readAll();

    QDomDocument document; QString error;

    if(!document.setContent(result, false, &error))
        dtkDebug() << "Error retrieving xml output out of " << url.toString() << error;

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
            
            if(properties.contains("singlecore")) {
                nc = 1; gpu->setCardinality(dtkDistributedGpu::Single);
            } else if(properties.contains("dualcore")) {
                nc = 2; gpu->setCardinality(dtkDistributedGpu::Dual);
            } else if(properties.contains("quadcore")) {
                nc = 4; gpu->setCardinality(dtkDistributedGpu::Quad);
            } else if(properties.contains("octocore")) {
                nc = 8; gpu->setCardinality(dtkDistributedGpu::Octo);
            }
            
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
            
            if(properties.contains("singlecore")) {
                nc = 1; cpu->setCardinality(dtkDistributedCpu::Single);
            } else if(properties.contains("dualcore")) {
                nc = 2; cpu->setCardinality(dtkDistributedCpu::Dual);
            } else if(properties.contains("quadcore")) {
                nc = 4; cpu->setCardinality(dtkDistributedCpu::Quad);
            } else if(properties.contains("octocore")) {
                nc = 8; cpu->setCardinality(dtkDistributedCpu::Octo);
            }
            
            for(int i = 0; i < nc; i++)
                *cpu << new dtkDistributedCore(cpu);

            *node << cpu;
        }

        d->nodes.prepend(node);
    }
}
