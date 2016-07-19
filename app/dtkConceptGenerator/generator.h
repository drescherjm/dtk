// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include <QtCore>
#include <QtDebug>

void generate(QString target,QMap<QString, QString> pairs,QString path);

QString readAndReplace(QString filePath, QMap<QString,QString> pairs);

//
// generator.h ends here
