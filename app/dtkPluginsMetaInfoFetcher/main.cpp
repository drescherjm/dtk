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

namespace dtkPluginsMetaInfoFetcher {

}

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);
    application.setApplicationName("dtkPluginsMetaInfoFetcher");
    application.setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Fetches meta information from a plugin");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("plugin", "The plugin from which information is fetched");
    parser.process(application);

    if(!parser.positionalArguments().count())
        parser.showHelp();

    QString plugin = parser.positionalArguments().at(0);

    if(!QLibrary::isLibrary(plugin)) {
        qDebug() << "plugin is not a  library.";
        return 1;
    }

    QPluginLoader *loader = new QPluginLoader(plugin);

    qDebug() << loader->metaData().toVariantMap();

    delete loader;

    return 0;
}

//
// main.cpp ends here
