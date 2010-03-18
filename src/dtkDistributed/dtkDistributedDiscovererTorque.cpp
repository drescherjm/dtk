/* dtkDistributedDiscovererTorque.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Mar 17 09:55:42 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 17 17:00:02 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 47
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedDiscovererTorque.h"

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

        if(state == "free")
            qDebug() << "- " << DTK_COLOR_FG_GREEN << name << DTK_NO_COLOR;
       
        if(state == "job-exclusive")
            qDebug() << "- " << DTK_COLOR_FG_YELLOW << name << DTK_NO_COLOR;

        if(state == "down")
            qDebug() << "- " << DTK_COLOR_FG_RED << name << DTK_NO_COLOR;
        
        if(state == "offline")
            qDebug() << "- " << DTK_COLOR_BG_RED << name << DTK_NO_COLOR;
    }
}
