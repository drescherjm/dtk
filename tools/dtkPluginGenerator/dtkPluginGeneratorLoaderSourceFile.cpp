/* dtkPluginGeneratorLoaderSourceFile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Mar 11 14:29:46 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 11 19:49:08 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPluginGenerator.h"

bool dtkPluginGenerator::generateLoaderSourceFile(void)
{
    QFile loaderSourceFile(d->target.absoluteFilePath(QString(d->plugin).append("PluginLoader.cpp")));

    if(!loaderSourceFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open" << QString(d->plugin).append("PluginLoader.cpp") << "for writing";
	return false;
    }

    QTextStream stream(&loaderSourceFile);

    stream << QString(
	"/* %1PluginLoader.cpp --- \n"
	" * \n"
	" * Author:\n"
	" * Copyright (C)\n"
	" * Created:\n"
	" * Version: $Id$\n"
	" * Last-Updated:\n"
	" *           By:\n"
	" *     Update #:\n"
	" */\n"
	"\n"
	"/* Commentary: \n"
	" * \n"
	" */\n"
	"\n"
	"/* Change log:\n"
	" * \n"
	" */\n"
	"\n"
	"#include \"%1PluginLoader.h\"\n"
	"\n"
	"static %1Plugin *plugin_instance = NULL;\n"
	"\n"
	"%1Plugin *plugin_create_instance(void)\n"
	"{\n"
	"    if (plugin_instance == NULL)\n"
	"        plugin_instance = new %1Plugin;\n"
	"\n"
	"    return plugin_instance;\n"
	"}\n"
	"\n"
	"void plugin_destroy_instance(void)\n"
	"{\n"
	"    if (plugin_instance == NULL)\n"
	"        delete plugin_instance;\n"
	"\n"
	"    plugin_instance = NULL;\n"
	"}\n"
	"\n"
	)
	.arg(d->plugin);

    loaderSourceFile.close();

    return true;
}
