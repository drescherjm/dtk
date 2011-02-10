/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 10 11:57:45 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 10 16:15:14 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 46
 */

/* Commentary: 
 * See credits at EOF.
 */

/* Change log:
 * 
 */

#include "dtkDeploy.h"

#include <QtCore>

int main(int argc, char **argv)
{
    QString appBundlePath;
    QStringList injection;

    if (argc > 1)
        appBundlePath = QString::fromLocal8Bit(argv[1]);

    if (argc < 2 || appBundlePath.startsWith("-")) {
        qDebug() << "Usage: dtkDeploy app-bundle [options]";
        qDebug() << "";
        qDebug() << "Options:";
        qDebug() << "   -verbose=<0-3> : 0 = no output, 1 = error/warning (default), 2 = normal, 3 = debug";
        qDebug() << "   -no-strip      : Don't run 'strip' on the binaries";
        qDebug() << "   -use-debug-libs: Deploy with debug versions of frameworks and plugins (implies -no-strip)";
        qDebug() << "   -inject=<dir>  : Repeatable option. Specifies a dtk build directory containing plugins to be";
        qDebug() << "                    injected into the bundle";
        qDebug() << "";
        qDebug() << "dtkDeploy takes an application bundle as input and makes it";
        qDebug() << "self-contained by copying in the Qt frameworks and plugins that";
        qDebug() << "the application uses.";

        return 0;
    }

    if (appBundlePath.endsWith("/"))
        appBundlePath.chop(1);

    if (QDir().exists(appBundlePath) == false) {
        qDebug() << "Error: Could not find app bundle" << appBundlePath;
        return 0;
    }

    bool useDebugLibs = false;
    extern bool runStripEnabled;

    for (int i = 2; i < argc; ++i) {

        QByteArray argument = QByteArray(argv[i]);

        if (argument == QByteArray("-no-strip")) {
            LogDebug() << "Argument found:" << argument;
            runStripEnabled = false;
        } else if (argument == QByteArray("-use-debug-libs")) {
            LogDebug() << "Argument found:" << argument;
            useDebugLibs = true;
            runStripEnabled = false;
        } else if (argument.startsWith(QByteArray("-verbose"))) {
            LogDebug() << "Argument found:" << argument;
            int index = argument.indexOf("=");
            bool ok = false;
            int number = argument.mid(index+1).toInt(&ok);
            if (!ok)
                LogError() << "Could not parse verbose level";
            else
                logLevel = number;

            // --

        } else if (argument.startsWith(QByteArray("-inject"))) {
            LogDebug() << "Argument found:" << argument;

            int index = argument.indexOf("=");

            QString directory = argument.mid(index+1);
            directory = directory.split(" ").first();
            if (directory.isNull())
                LogError() << "Could not parse injection directory";

            injection << directory;

            // --

        } else if (argument.startsWith("-")) {
            LogError() << "Unknown argument" << argument << "\n";
            return 0;
        }
     }

    DeploymentInfo deploymentInfo  = deployQtFrameworks(appBundlePath, useDebugLibs);

    if (deploymentInfo.qtPath.isEmpty())
        deploymentInfo.pluginPath = "/Developer/Applications/Qt/plugins"; // Assume binary package.
    else
        deploymentInfo.pluginPath = deploymentInfo.qtPath + "/plugins";
    
    LogNormal();
    deployPlugins(appBundlePath, deploymentInfo, useDebugLibs);
    createQtConf(appBundlePath);

    foreach(QString directory, injection) {
        qDebug() << "Injecting plugins from" << directory;
        deployDtkPlugins(appBundlePath, deploymentInfo, directory);
    }
}

/* **************************************************************
 * Credits
 * ************************************************************** */

/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the tools applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
****************************************************************************/
