/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar 16 14:49:31 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 17 09:38:39 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 18
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

#include <dtkSsh/dtkSshController.h>

int main(int argc, char **argv)
{
    if(argc != 2) {
        dtkOutput() << "Usage: " << QString(argv[0]) << " [host]";
        return 0;
    }

    QString result;

    dtkSshController::instance()->createConnection(QUrl(QString(argv[1])));
    dtkSshController::instance()->execute(QString("qstat -x"), result);

    dtkDebug() << DTK_COLOR_FG_RED << result << DTK_NO_COLOR;
    
    return 0;
}
