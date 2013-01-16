#include "dtkGenerator.h"
#include <QString>
#include <QRegExp>
#include <QFileInfo>
#include <QDir>


dtkGenerator::dtkGenerator(void)
{
    this->d = new dtkGeneratorPrivate;
}

dtkGenerator::~dtkGenerator(void)
{
    delete this->d;
    this->d = NULL;
}


//! Set parameters
void dtkGenerator::setType(const QString& type)
{
    d->type = type;
}

void dtkGenerator::setInterface(const QString& interface)
{
    d->interface = interface;
    d->interfaceBaseName = QFileInfo(interface).baseName();
}

void dtkGenerator::setApplicationPrefix(const QString& applicationPrefix)
{
    d->applicationPrefix = applicationPrefix.toLower();
}

void dtkGenerator::setOutputDirectory(const QString& outputDirectory)
{
    d->outputDirectory = outputDirectory;
}

void dtkGenerator::setAbstractionLevel(const QString& abstractionLevel)
{
    d->abstractionLevel = abstractionLevel;
}

void dtkGenerator::setName(const QString& name)
{
    d->name = name;
}


//! Check parameters
bool dtkGenerator::checkParameters(void)
{
    //! Check type
    if (d->type.isEmpty()) {
        qDebug() << "The option \"type\" is mandatory.";
        return false;
    }

    if (d->type != "core" && d->type != "plugin" && d->type != "composer") {
        qDebug() << "\"type\" =  core, plugin or composer.";
        return false;
    }

    //! Check interface
    if (d->interface.isEmpty()) {
        qDebug() << "The option \"interface\" is mandatory.";
        return false;
    }

    QRegExp interfaceRegExp = QRegExp("^([a-z]+)([A-Z][a-z]+)?(?:Abstract)?(Data|Process|View)([A-Z]\\w+)?\\.(h|hpp)$");
    int pos = 0;

    if (interfaceRegExp.indexIn(d->interface, pos) != -1) {
        d->dtkInterface = true;

        if (interfaceRegExp.cap(1) != "dtk") {
            d->applicationPrefix = interfaceRegExp.cap(1);
            d->dtkInterface = false;
        }

        if (interfaceRegExp.cap(2) == "Abstract")
            d->applicationLayer = "";
        else
            d->applicationLayer = interfaceRegExp.cap(2);

        d->dtkType = interfaceRegExp.cap(3);

        d->applicationSpecificationType = interfaceRegExp.cap(4);

        d->headerExtension = interfaceRegExp.cap(5);
    }
    else {
        qDebug() << "Your interface doesn't follow the naming convention.";
        return false;
    }
#if 0
    qDebug() << "applicationPrefix : " << d->applicationPrefix;
    qDebug() << "applicationLayer : " << d->applicationLayer;
    qDebug() << "dtkType : " << d->dtkType;
    qDebug() << "applicationSpecificationType : " << d->applicationSpecificationType;
    qDebug() << "headerExtension : " << d->headerExtension;
#endif
    //! Check output directory
    //! default value = "."
    if (d->outputDirectory.isEmpty())
        d->outputDirectory = ".";

    QFileInfo outputDirectoryFileInfo = QFileInfo(d->outputDirectory);

    if (!outputDirectoryFileInfo.isDir() || !outputDirectoryFileInfo.isWritable()) {
        qDebug() << "You have to provide a writable directory.";
        return false;
    }

    //! Check abstraction level
    if (d->type == "core") {
        //! default value = "default"
        if (d->abstractionLevel.isEmpty())
            d->abstractionLevel = "default";

        if (!(d->abstractionLevel == "pure" || d->abstractionLevel == "default" || d->abstractionLevel == "concrete")) {
            qDebug() << "The option \"abstractionLevel\" is mandatory for type = core.";
            return false;
        }
    }

    //! Check name
    if (d->type != "composer" && d->name.isEmpty()) {
        qDebug() << "The option \"name\" is mandatory for \"type\" = core or plugin.";
        return false;
    }

    //! Check applicationPrefix
    if (d->applicationPrefix.isEmpty()) {
        qDebug() << "You have to provide an applicationPrefix if you picked a DTK interface.";
        return false;
    }

    return true;
}

bool dtkGenerator::run(void)
{
    if (!checkParameters())
        return false;

    if (!d->target.setCurrent(d->outputDirectory)) {
        qWarning() << "Unable to move to output directory.";
        return false;
    }

    if (d->type == "core") {
        d->coreName = d->applicationPrefix;

        if (d->abstractionLevel != "concrete")
            d->coreName += "Abstract";

        d->coreName += d->dtkType;
        d->coreName += d->applicationSpecificationType;

        d->name[0] = d->name[0].toUpper();
        d->coreName += d->name;

        return generateCore();
    }
    else if (d->type == "plugin") {
        d->pluginName = d->name + d->dtkType + d->applicationSpecificationType;

        if (!d->target.mkdir(d->pluginName)) {
            qWarning() << "Unable to create plugin directory.";
            return false;
        }

        if (!d->target.cd(d->pluginName)) {
            qWarning() << "Unable to move to plugin directory.";
            return false;
        }

        return generatePlugin();
    }
    else if (d->type == "composer") {
        d->composerName = d->applicationPrefix + "ComposerNode" + d->dtkType + d->applicationSpecificationType;
        return generateComposer();
    }
    
    return false;
}

bool dtkGenerator::generateCore(void) {
    return generateCoreSourceFile() && generateCorePrivateFile() && generateCoreHeaderFile();
}

bool dtkGenerator::generatePlugin(void) {
    return  generateCMakeLists() &&
            generateTypeHeaderFile() &&
            generateTypeSourceFile() &&
            generatePluginConfigFile() &&
            generatePluginHeaderFile() &&
            generatePluginSourceFile() &&
            generateExportHeaderFile() &&
            generateHelpCollectionFile() &&
            generateHelpConfigurationFile();
}

bool dtkGenerator::generateComposer(void) {
    return generateComposerSourceFile() && generateComposerHeaderFile();
}

//! Core files
bool dtkGenerator::generateCoreSourceFile(void) {
    QFile targetFile(d->target.absoluteFilePath(QString(d->coreName).append(".cpp")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning() << "dtkGenerator: unable to open CMakeLists.txt for writing";
    return false;
    }

    QFile templateFile(":/templates/core/interface.cpp");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);

    stream << QString(templateFile.readAll()).arg(d->coreName)                    //! %1
                                             .arg(d->dtkType)                     //! %2
                                             .arg(d->interfaceBaseName);          //! %3

    targetFile.close();

    templateFile.close();

    return true;
}

bool dtkGenerator::generateCorePrivateFile(void) {
    QFile targetFile(d->target.absoluteFilePath(QString(d->coreName).append("_p.h")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning() << "dtkGenerator: unable to open CMakeLists.txt for writing";
    return false;
    }

    QFile templateFile(":/templates/core/interface_p.h");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);

    QString includePrivateFile;

    if (d->dtkInterface)
        includePrivateFile = "<dtkCore/" + d->interfaceBaseName + "_p.h>";
    else
        includePrivateFile = "\"" + d->interfaceBaseName + "_p.h\"";

    stream << QString(templateFile.readAll()).arg(d->coreName)                    //! %1
                                             .arg(d->coreName.toUpper())          //! %2
                                             .arg(d->interfaceBaseName)           //! %3
                                             .arg(includePrivateFile);            //! %4
    targetFile.close();

    templateFile.close();

    return true;
}

bool dtkGenerator::generateCoreHeaderFile(void) {
    QFile targetFile(d->target.absoluteFilePath(QString(d->coreName).append(".h")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning() << "dtkGenerator: unable to open CMakeLists.txt for writing";
    return false;
    }

    QFile templateFile(":/templates/core/interface.h");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);

    QString includeFile;

    if (d->dtkInterface)
        includeFile = "<dtkCore/" + d->interface + ">";
    else
        includeFile = "\"" + d->interface + "\"";

    stream << QString(templateFile.readAll()).arg(d->coreName)                    //! %1
                                             .arg(d->coreName.toUpper())          //! %2
                                             .arg(d->applicationPrefix)           //! %3
                                             .arg(d->applicationPrefix.toUpper()) //! %4
                                             .arg(d->interfaceBaseName)           //! %5
                                             .arg(includeFile);                   //! %6

    targetFile.close();

    templateFile.close();

    return true;
}


//! Plugin files
// /////////////////////////////////////////////////////////////////
// CMakeLists.txt
// /////////////////////////////////////////////////////////////////
bool dtkGenerator::generateCMakeLists(void)
{
    QFile targetFile(d->target.absoluteFilePath("CMakeLists.txt"));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning() << "dtkGenerator: unable to open CMakeLists.txt for writing";
	return false;
    }

    QFile templateFile(":/templates/plugin/cmake");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);

    stream << QString(templateFile.readAll())
                        .arg(QString(d->pluginName));

    targetFile.close();

    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Type header file
// /////////////////////////////////////////////////////////////////
bool dtkGenerator::generateTypeHeaderFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->pluginName).append(".h")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning() << "dtkGenerator: unable to open" << QString(d->pluginName).append(".h") << "for writing";
	return false;
    }

    QFile templateFile(":/templates/plugin/type.h");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    QString includeFile;

    if (d->dtkInterface)
        includeFile = "<dtkCore/" + d->interfaceBaseName + ".h>";
    else
        includeFile = "<supCore/" + d->interfaceBaseName + ".h>";

    QString PluginName = d->pluginName;
    PluginName[0] = PluginName[0].toUpper();

    stream << QString(templateFile.readAll())
                        .arg(d->pluginName)
                        .arg(d->pluginName.toUpper())
                        .arg(d->dtkType)
                        .arg(PluginName)
                        .arg(d->interfaceBaseName)
                        .arg(includeFile);


    
    targetFile.close();
    
    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Type source file
// /////////////////////////////////////////////////////////////////
bool dtkGenerator::generateTypeSourceFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->pluginName).append(".cpp")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "dtkGenerator: unable to open" << QString(d->pluginName).append(".cpp") << "for writing";
        return false;
    }

    QFile templateFile(":/templates/plugin/type.cpp");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    
    QString PluginName = d->pluginName;
    PluginName[0] = PluginName[0].toUpper();
    QString includeFile;

    if (d->dtkInterface)
        includeFile = "<dtkCore/" + d->interfaceBaseName + "_p.h>";
    else
        includeFile = "<supCore/" + d->interfaceBaseName + "_p.h>";


    stream << QString(templateFile.readAll())
                        .arg(d->pluginName)
                        .arg(includeFile)
                        .arg(d->interfaceBaseName)
                        .arg(d->dtkType)
                        .arg(PluginName);
    
    targetFile.close();
    
    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Plugin config file
// /////////////////////////////////////////////////////////////////
bool dtkGenerator::generatePluginConfigFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->pluginName).append("PluginConfig.h.in")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "dtkGenerator: unable to open" << QString(d->pluginName).append("PluginConfig.h.in") << "for writing";
        return false;
    }

    QFile templateFile(":/templates/plugin/config.h");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    
    stream << QString(templateFile.readAll())
                        .arg(QString(d->pluginName).toUpper())
                        .arg(QString(d->pluginName));
    
    targetFile.close();
    
    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Plugin header file
// /////////////////////////////////////////////////////////////////
bool dtkGenerator::generatePluginHeaderFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->pluginName).append("Plugin.h")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "dtkGenerator: unable to open" << QString(d->pluginName).append("Plugin.h") << "for writing";
        return false;
    }

    QFile templateFile(":/templates/plugin/plugin.h");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    
    stream << QString(templateFile.readAll())
                        .arg(QString(d->pluginName))
                        .arg(QString(d->pluginName).toUpper());
    
    targetFile.close();
    
    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Plugin source file
// /////////////////////////////////////////////////////////////////
bool dtkGenerator::generatePluginSourceFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->pluginName).append("Plugin.cpp")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "dtkGenerator: unable to open" << QString(d->pluginName).append("Plugin.cpp") << "for writing";
        return false;
    }

    QFile templateFile(":/templates/plugin/plugin.cpp");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    
    stream << QString(templateFile.readAll())
                        .arg(QString(d->pluginName));
    
    targetFile.close();
    
    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Export file
// /////////////////////////////////////////////////////////////////
bool dtkGenerator::generateExportHeaderFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->pluginName).append("PluginExport.h")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "dtkGenerator: unable to open" << QString(d->pluginName).append("PluginExport.h") << "for writing";
        return false;
    }

    QFile templateFile(":/templates/plugin/export.h");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);
    
    stream << QString(templateFile.readAll())
                        .arg(QString(d->pluginName))
                        .arg(QString(d->pluginName).toUpper());
    
    targetFile.close();
    
    templateFile.close();

    return true;
}

// /////////////////////////////////////////////////////////////////
// Help collection file
// /////////////////////////////////////////////////////////////////
bool dtkGenerator::generateHelpCollectionFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->pluginName).append("Plugin.qhcp.in")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "dtkGenerator: unable to open" << QString(d->pluginName).append("Plugin.qhcp.in") << "for writing";
        return false;
    }

    QFile templateFile(":/templates/plugin/qhcp");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkGenerator: unable to open template file " << templateFile.fileName() << " for reading";
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
bool dtkGenerator::generateHelpConfigurationFile(void)
{
    QFile targetFile(d->target.absoluteFilePath(QString(d->pluginName).append("Plugin.doxyfile.in")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "dtkGenerator: unable to open" << QString(d->pluginName).append("Plugin.doxyfile.in") << "for writing";
        return false;
    }

    QFile templateFile(":/templates/plugin/doxyfile");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkGenerator: unable to open template file " << templateFile.fileName() << " for reading";
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
/*
bool dtkGenerator::generateReadmeFile(void)
{
    QFile targetFile(d->target.absoluteFilePath("README.txt"));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "dtkGenerator: unable to open CMakeLists.txt for writing";
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
bool dtkGenerator::generateCopyingFile(void)
{
    QFile targetFile(d->target.absoluteFilePath("COPYING.txt"));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "dtkGenerator: unable to open COPYING.txt for writing";
        return false;
    }

    QFile templateFile(QString(":/templates/licenses/").append(d->license));
    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);

    stream << QString(templateFile.readAll());

    targetFile.close();

    return true;
}
*/


//! Composer files
bool dtkGenerator::generateComposerSourceFile(void) {
    QFile targetFile(d->target.absoluteFilePath(QString(d->composerName).append(".cpp")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning() << "dtkGenerator: unable to open CMakeLists.txt for writing";
    return false;
    }

    QFile templateFile(":/templates/composer/node.cpp");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);

    stream << QString(templateFile.readAll()).arg(d->composerName)                //! %1
                                             .arg(d->dtkType);                    //! %2
    targetFile.close();

    templateFile.close();

    return true;
}

bool dtkGenerator::generateComposerHeaderFile(void) {
    QFile targetFile(d->target.absoluteFilePath(QString(d->composerName).append(".h")));

    if(!targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning() << "dtkGenerator: unable to open CMakeLists.txt for writing";
    return false;
    }

    QFile templateFile(":/templates/composer/node.h");

    if(!templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "dtkGenerator: unable to open template file " << templateFile.fileName() << " for reading";
        return false;
    }

    QTextStream stream(&targetFile);

    stream << QString(templateFile.readAll()).arg(d->composerName)                //! %1
                                             .arg(d->composerName.toUpper())      //! %2
                                             .arg(d->applicationPrefix)           //! %3
                                             .arg(d->applicationPrefix.toUpper()) //! %4
                                             .arg(d->dtkType);                    //! %5
    targetFile.close();

    templateFile.close();

    return true;
}
