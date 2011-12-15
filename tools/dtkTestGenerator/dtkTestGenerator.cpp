/* dtkTestGenerator.cpp ---
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar  9 21:41:18 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Sep  5 14:58:40 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 187
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkTestGenerator.h"

dtkTestGenerator::dtkTestGenerator(void)
{
    this->d = new dtkTestGeneratorPrivate;
}

dtkTestGenerator::~dtkTestGenerator(void)
{
    delete this->d;
    this->d = NULL;
}

void dtkTestGenerator::setOutputDirectory(const QString& directory)
{
    d->output = directory;
}

void dtkTestGenerator::setClassName(const QString& className)
{
    d->className = className;
}

bool dtkTestGenerator::run(void)
{
    d->parent = QDir(d->output);

    if(!d->parent.exists()) {
        qWarning() << "dtkTestGenerator: parent directory is not valid.";
        return false;
    }

    d->classTestName = QString("%1Test")
            .arg(QString(d->className));

    /*
    if(!d->parent.mkdir(QString(d->classTestName))) {
        qWarning() << "dtkTestGenerator: unable to create target directory.";
        return false;
    }
    */

    d->target = QDir(d->parent);

    /*
    if(!d->target.cd(QString(d->classTestName))) {
        qWarning() << "dtkTestGenerator: unable to move to target directory.";
        return false;
    }
    */
    
    return /*generateCMakeLists() &&*/
            generateTestHeaderFile() &&
            generateTestSourceFile();
}

// /////////////////////////////////////////////////////////////////
// CMakeLists.txt
// /////////////////////////////////////////////////////////////////

bool dtkTestGenerator::generateCMakeLists(void)
{
    QFile targetFile(d->target.absoluteFilePath("CMakeLists.txt"));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "dtkTestGenerator: unable to open CMakeLists.txt for writing";
        return false;
    }

    QFile templateFile(":template/cmake");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkTestGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);

    stream << QString(templateFile.readAll()).arg(QString(d->classTestName));

    targetFile.close();

    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Type header file
// /////////////////////////////////////////////////////////////////

bool dtkTestGenerator::generateTestHeaderFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->classTestName).append(".h")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "dtkTestGenerator: unable to open" << QString(d->classTestName).append(".h") << "for writing";
        return false;
    }

    QFile templateFile(":template/test.h");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkTestGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    
    stream << QString(templateFile.readAll())
              .arg(QString(d->classTestName))
              .arg(QString(d->classTestName).toUpper());
    
    targetFile.close();
    
    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Type source file
// /////////////////////////////////////////////////////////////////

bool dtkTestGenerator::generateTestSourceFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->classTestName).append(".cpp")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "dtkTestGenerator: unable to open" << QString(d->classTestName).append(".cpp") << "for writing";
        return false;
    }

    QFile templateFile(":template/test.cpp");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkTestGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    
    stream << QString(templateFile.readAll())
              .arg(QString(d->classTestName));
    
    targetFile.close();
    
    templateFile.close();

    return true;
}
