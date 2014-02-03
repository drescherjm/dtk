/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Jan 30 00:19:02 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb  7 16:35:52 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 116
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QApplication>

#include "anyoption.h"

#include "dtkTestGeneratorMainWindow.h"
#include "dtkTestGenerator.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    AnyOption options;
    options.addUsage(QString("Usage: %1 --help | --console | [--output path --class className").arg(argv[0]).toAscii());
    options.addUsage("");
    options.addUsage("--help                Displays this message.");
    options.addUsage("--console             Run the gui version.");
    options.addUsage("--output [path]       Output directory for the test skeleton.");
    options.addUsage("--class [className]   Class to be tested.");
    options.addUsage("--quiet               Process quietly (non gui generation only).");

    options.setFlag("help");
    options.setFlag("console");

    options.setOption("output");
    options.setOption("class");
    options.setOption("quiet");

    options.processCommandArgs(argc, argv);

    if(options.getFlag("help")) {
        options.printUsage();
        return 0;
    }

    if(options.getFlag("console")) {

        bool paramsOk = options.getValue("output") && options.getValue("class");

        if( !paramsOk ) {
            options.printUsage();
            return 1;
        }

        if(!options.getFlag("quiet")) {
            qDebug() << "output = " << options.getValue("output");
            qDebug() << "class = " << options.getValue("class");
        }

        dtkTestGenerator generator;
        generator.setOutputDirectory(options.getValue("output"));
        generator.setClassName(options.getValue("class"));

        bool resultGenerator = generator.run();

        if(!options.getFlag("quiet")) {
            if(resultGenerator)
                qDebug() << "Generation succeeded.";
            else
                qDebug() << "Test generation: Generation failed.";
        }

    } else {

        dtkTestGeneratorMainWindow generator;
        generator.show();
        return app.exec();

    }
}
