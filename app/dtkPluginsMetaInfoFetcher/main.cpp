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

#include <QtCore>

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);
    application.setApplicationName("dtkPluginsMetaInfoFetcher");
    application.setApplicationVersion("1.0");

    QCommandLineOption version_option(QStringList() << "v" << "version", "Prints the version of the plugin.");
    QCommandLineOption depende_option(QStringList() << "d" << "dependencies", "Prints the dependencies of the plugin.");

    QCommandLineParser parser;
    parser.setApplicationDescription("Fetches meta information from a plugin.");
    parser.addHelpOption();
    parser.addOption(version_option);
    parser.addOption(depende_option);
    parser.addPositionalArgument("plugin", "The plugin from which information is fetched.");
    parser.process(application);

    if (!parser.positionalArguments().count())
        parser.showHelp();

    QString plugin = parser.positionalArguments().at(0);

    if (!QLibrary::isLibrary(plugin)) {
        qDebug() << "plugin is not a  library.";
        return 1;
    }

    QPluginLoader *loader = new QPluginLoader(plugin);

    if (parser.isSet(version_option))
        qDebug() << loader->metaData().toVariantMap().value("MetaData").toMap().value("version");
    else if (parser.isSet(depende_option))
        qDebug() << loader->metaData().toVariantMap().value("MetaData").toMap().value("dependencies");
    else
        qDebug() << loader->metaData().toVariantMap();

    delete loader;

    return 0;
}

//
// main.cpp ends here
