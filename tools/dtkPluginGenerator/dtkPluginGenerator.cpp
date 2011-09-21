/* dtkPluginGenerator.cpp --- 
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

void dtkPluginGenerator::setDescription(const QString& desc)
{
    d->description = desc;
}

void dtkPluginGenerator::setLicense(const QString& license)
{
    d->license = license;
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
        && generatePluginConfigFile()
        && generatePluginHeaderFile()
        && generatePluginSourceFile()
        && generateExportHeaderFile()
        && generateHelpCollectionFile()
        && generateHelpConfigurationFile()
        && generateReadmeFile()
        && generateCopyingFile();
}

// /////////////////////////////////////////////////////////////////
// CMakeLists.txt
// /////////////////////////////////////////////////////////////////

bool dtkPluginGenerator::generateCMakeLists(void)
{
    QFile targetFile(d->target.absoluteFilePath("CMakeLists.txt"));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open CMakeLists.txt for writing";
	return false;
    }

    QFile templateFile(":template/cmake");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkPluginGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);

    stream << QString(templateFile.readAll()).arg(QString(d->plugin));

    targetFile.close();

    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Type header file
// /////////////////////////////////////////////////////////////////

bool dtkPluginGenerator::generateTypeHeaderFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->plugin).append(".h")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open" << QString(d->plugin).append(".h") << "for writing";
	return false;
    }

    QFile templateFile(":template/type.h");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkPluginGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    
    stream << QString(templateFile.readAll())
        .arg(QString(d->plugin))
	.arg(QString(d->plugin).toUpper())
	.arg(QString(d->type))
	.arg(QString(d->plugin).remove(d->prefix).prepend(QString(d->prefix).replace(0, 1, QString(d->prefix).left(1).toUpper())));
    
    targetFile.close();
    
    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Type source file
// /////////////////////////////////////////////////////////////////

bool dtkPluginGenerator::generateTypeSourceFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->plugin).append(".cpp")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open" << QString(d->plugin).append(".cpp") << "for writing";
	return false;
    }

    QFile templateFile(":template/type.cpp");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkPluginGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    
    stream << QString(templateFile.readAll())
        .arg(QString(d->plugin))
	.arg(QString(d->type))
	.arg(QString(d->plugin).remove(d->prefix).prepend(QString(d->prefix).replace(0, 1, QString(d->prefix).left(1).toUpper())));
    
    targetFile.close();
    
    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Plugin config file
// /////////////////////////////////////////////////////////////////

bool dtkPluginGenerator::generatePluginConfigFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->plugin).append("PluginConfig.h.in")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open" << QString(d->plugin).append("PluginConfig.h.in") << "for writing";
	return false;
    }

    QFile templateFile(":template/config.h");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkPluginGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    
    stream << QString(templateFile.readAll())
	.arg(QString(d->plugin).toUpper())
        .arg(QString(d->plugin));
    
    targetFile.close();
    
    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Plugin header file
// /////////////////////////////////////////////////////////////////

bool dtkPluginGenerator::generatePluginHeaderFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->plugin).append("Plugin.h")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open" << QString(d->plugin).append("Plugin.h") << "for writing";
	return false;
    }

    QFile templateFile(":template/plugin.h");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkPluginGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    
    stream << QString(templateFile.readAll())
        .arg(QString(d->plugin))
	.arg(QString(d->plugin).toUpper());
    
    targetFile.close();
    
    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Plugin source file
// /////////////////////////////////////////////////////////////////

bool dtkPluginGenerator::generatePluginSourceFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->plugin).append("Plugin.cpp")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open" << QString(d->plugin).append("Plugin.cpp") << "for writing";
	return false;
    }

    QFile templateFile(":template/plugin.cpp");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkPluginGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    
    stream << QString(templateFile.readAll()).arg(QString(d->plugin));
    
    targetFile.close();
    
    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Export file
// /////////////////////////////////////////////////////////////////

bool dtkPluginGenerator::generateExportHeaderFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->plugin).append("PluginExport.h")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open" << QString(d->plugin).append("PluginExport.h") << "for writing";
	return false;
    }

    QFile templateFile(":template/export.h");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkPluginGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    
    stream << QString(templateFile.readAll()).arg(QString(d->plugin)).arg(QString(d->plugin).toUpper());
    
    targetFile.close();
    
    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Help collection file
// /////////////////////////////////////////////////////////////////

bool dtkPluginGenerator::generateHelpCollectionFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->plugin).append("Plugin.qhcp.in")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open" << QString(d->plugin).append("Plugin.qhcp.in") << "for writing";
	return false;
    }

    QFile templateFile(":template/qhcp");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkPluginGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    
    stream << QString(templateFile.readAll());
    
    targetFile.close();
    
    templateFile.close();

    return true;
}


// /////////////////////////////////////////////////////////////////
// Help configuration file
// /////////////////////////////////////////////////////////////////

bool dtkPluginGenerator::generateHelpConfigurationFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->plugin).append("Plugin.doxyfile.in")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open" << QString(d->plugin).append("Plugin.doxyfile.in") << "for writing";
	return false;
    }

    QFile templateFile(":template/doxyfile");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkPluginGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    
    stream << QString(templateFile.readAll());
    
    targetFile.close();
    
    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// README file
// /////////////////////////////////////////////////////////////////

bool dtkPluginGenerator::generateReadmeFile(void)
{
    QFile targetFile(d->target.absoluteFilePath("README.txt"));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open CMakeLists.txt for writing";
	return false;
    }

    QTextStream stream(&targetFile);

    stream << d->description;

    targetFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// COPYING file
// /////////////////////////////////////////////////////////////////

bool dtkPluginGenerator::generateCopyingFile(void)
{
    QFile targetFile(d->target.absoluteFilePath("COPYING.txt"));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open COPYING.txt for writing";
	return false;
    }

    QFile templateFile(QString(":template/license/").append(d->license));
    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkPluginGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);

    stream << QString(templateFile.readAll());

    targetFile.close();

    return true;
}
