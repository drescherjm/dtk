/* dtkPluginGeneratorLoaderHeaderFile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Mar 11 14:29:12 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 11 19:49:33 2009 (+0100)
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

bool dtkPluginGenerator::generateLoaderHeaderFile(void)
{
    QFile loaderHeaderFile(d->target.absoluteFilePath(QString(d->plugin).append("PluginLoader.h")));

    if(!loaderHeaderFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open" << QString(d->plugin).append("PluginLoader.h") << "for writing";
	return false;
    }
        
    QTextStream stream(&loaderHeaderFile);

    stream << QString(
	"/* %1PluginLoader.h --- \n"
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
	"#ifndef %2PLUGINLOADER_H\n"
	"#define %2PLUGINLOADER_H\n"
	"\n"
	"#include \"%1Plugin.h\"\n"
	"#include \"%1PluginExport.h\"\n"
	"\n"
	"#ifdef __cplusplus\n"
	"extern \"C\" {\n"
	"#endif\n"
	"\n"
	"%2PLUGIN_EXPORT %1Plugin *plugin_create_instance(void);\n"
	"%2PLUGIN_EXPORT void plugin_destroy_instance(void);\n"
	"\n"
	"#ifdef __cplusplus\n"
	"}\n"
	"#endif\n"
	"\n"
	"#endif\n"
	"\n"
	)
	.arg(QString(d->plugin))
	.arg(QString(d->plugin).toUpper());

    loaderHeaderFile.close();

    return true;
}

