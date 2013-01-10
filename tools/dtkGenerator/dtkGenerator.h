#ifndef DTKGENERATOR_H
#define DTKGENERATOR_H

#include <QtCore>

class dtkGeneratorPrivate
{
public:
    //! Parameters coming from the command line or the wizard:
    QString type;
    QString interface;
    QString outputDirectory;
    QString abstractionLevel;
    QString name;

    /*! Parameters that can be guessed from the interface naming convention:
        interface = applicationPrefix + applicationLayer + (Abstract)? + dtkType + applicationSpecificationType
      */
    QString interfaceBaseName;
    bool dtkInterface;

    QString applicationPrefix;
    QString applicationLayer;
    QString dtkType;
    QString applicationSpecificationType;
    QString headerExtension;

    //! Computed names following naming conventions
    QString coreName;
    QString pluginName;
    QString composerName;

    //! Output directory
    QDir target;
};

class dtkGenerator
{
public:
    dtkGenerator(void);
   ~dtkGenerator(void);

    void setType(const QString& type);
    void setInterface(const QString& interface);
    void setApplicationPrefix(const QString& applicationPrefix);
    void setOutputDirectory(const QString& outputDirectory);
    void setAbstractionLevel(const QString& abstractionLevel);
    void setName(const QString& name);

   bool checkParameters(void);
   bool run(void);

protected:
   bool generateCore(void);
   bool generatePlugin(void);
   bool generateComposer(void);

//! Core files
protected:
   bool generateCoreSourceFile(void);
   bool generateCorePrivateFile(void);
   bool generateCoreHeaderFile(void);

//! Plugin files
protected:
   bool generateCMakeLists(void);
   bool generateTypeHeaderFile(void);
   bool generateTypeSourceFile(void);
   bool generatePluginConfigFile(void);
   bool generatePluginHeaderFile(void);
   bool generatePluginSourceFile(void);
   bool generateExportHeaderFile(void);
   bool generateHelpCollectionFile(void);
   bool generateHelpConfigurationFile(void);
   //bool generateReadmeFile(void);
   //bool generateCopyingFile(void);

//! Composer files
protected:
   bool generateComposerSourceFile(void);
   bool generateComposerHeaderFile(void);

private:
   dtkGeneratorPrivate *d;
};

#endif
