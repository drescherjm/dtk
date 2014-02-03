#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include "anyoption.h"

#include "dtkGeneratorWizard.h"
#include "dtkGenerator.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(dtkGenerator);

    QApplication app(argc, argv);

    AnyOption options;
    options.addUsage(QString("Usage: %1 -h | [-c [-q]] -t core [-a abstractionLevelName] -i interfaceName [-p applicationPrefixName] [-n Name] [-d dirName]").arg(argv[0]).toAscii());
    options.addUsage("");
    options.addUsage("-h --help                                 Displays this message.");

    options.addUsage("-c --console                              Run the console mode.");
    options.addUsage("-q --quiet                                Run quietly in console mode.");

    options.addUsage("-t --type      [typeName]                 Generate a \"core\" class, a \"plugin\" or a \"composer\" class.");
    options.addUsage("-i --interface [interfaceName]            The type generated will inherit or wrapp the \"interfaceName\" class.");
    options.addUsage("-p --prefix    [applicationPrefixName]    Specify your application prefix.");
    options.addUsage("-d --dir       [outputDirName]                  Where to generate the files.");

    options.addUsage("-a --abstract  [abstractionLevelName]     Choose to generate a \"pure\" abstract, \"default\" with implementation or a \"concrete\" core class.");
    options.addUsage("-n --name      [Name]                     Specify your core class or plugin with a name.");


    options.setFlag("help",'h');
    options.setFlag("console",'c');
    options.setFlag("quiet",'q');

    options.setOption("type",'t');
    options.setOption("interface",'i');
    options.setOption("prefix",'p');
    options.setOption("dir",'d');
    options.setOption("abstract",'a');
    options.setOption("name",'n');

    options.processCommandArgs(argc, argv);

    if(options.getFlag("help")) {
        options.printUsage();
        return 0;
    }

    if(options.getFlag("console")) {
        dtkGenerator generator;

        generator.setType(options.getValue("type"));
        generator.setInterface(options.getValue("interface"));
        generator.setApplicationPrefix(options.getValue("prefix"));
        generator.setOutputDirectory(options.getValue("dir"));
        generator.setAbstractionLevel(options.getValue("abstract"));
        generator.setName(options.getValue("name"));

        if(!generator.checkParameters()) {
            options.printUsage();
            return 1;
        }

        bool resultGenerator = generator.run();

        if(!options.getFlag("quiet")) {
            if(resultGenerator) {
                qDebug() << "Generation succeeded.";
                return 0;
            }
            else {
                qDebug() << "Generation failed.";
                return 1;
            }
        }

    } else {
        QString translatorFileName = QLatin1String("qt_");
        translatorFileName += QLocale::system().name();
        QTranslator *translator = new QTranslator(&app);
        if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
            app.installTranslator(translator);

        dtkGeneratorWizard generator;
        generator.show();
        return app.exec();
    }
}
