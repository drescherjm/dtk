/* dtkPluginGenerator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar  9 21:41:18 2009 (+0100)
 * Version: $Id$
 * Last-Updated:  Tue Mar 24 08:47:54 2009
 *           By: Jean-Christophe Lombardo
 *     Update #: 84
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPluginGenerator.h"

dtkPluginGenerator::dtkPluginGenerator(void)
{
    this->d = new dtkPluginGeneratorPrivate;
}

dtkPluginGenerator::~dtkPluginGenerator(void)
{
    delete this->d;
    this->d = NULL;
}

void dtkPluginGenerator::setOutputDirectory(const QString& directory)
{
    d->output = directory;
}

void dtkPluginGenerator::setPrefix(const QString& prefix)
{
    d->prefix = prefix;
}

void dtkPluginGenerator::setSuffix(const QString& suffix)
{
    d->suffix = suffix;
}

void dtkPluginGenerator::setType(const QString& type)
{
    d->type = type;
}

bool dtkPluginGenerator::run(void)
{
    d->parent = QDir(d->output);

    if(!d->parent.exists()) {
        qWarning() << "dtkPluginGenerator: parent directory is not valid.";
        return false;
    }

    d->plugin = QString("%1%2%3")
        .arg(QString(d->prefix).toLower())
        .arg(d->type)
        .arg(d->suffix);

    if(!d->parent.mkdir(QString(d->plugin))) {
        qWarning() << "dtkPluginGenerator: unable to create target directory.";
        return false;
    }

    d->target = QDir(d->parent);

    if(!d->target.cd(QString(d->plugin))) {
        qWarning() << "dtkPluginGenerator: unable to move to target directory.";
        return false;
    }
    
    return generateCMakeLists()
        && generateTypeHeaderFile()
        && generateTypeSourceFile()
        && generatePluginHeaderFile()
        && generatePluginSourceFile()
        && generateLoaderHeaderFile()
        && generateLoaderSourceFile()
        && generateExportHeaderFile();
}
