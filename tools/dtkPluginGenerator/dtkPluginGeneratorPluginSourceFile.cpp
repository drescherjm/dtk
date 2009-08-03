/* dtkPluginGeneratorPluginSourceFile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Mar 11 14:27:57 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Aug  2 15:21:33 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPluginGenerator.h"

bool dtkPluginGenerator::generatePluginSourceFile(void)
{
    QFile pluginSourceFile(d->target.absoluteFilePath(QString(d->plugin).append("Plugin.cpp")));

    if(!pluginSourceFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open" << QString(d->plugin).append("Plugin.cpp") << "for writing";
	return false;
    }

    QTextStream stream(&pluginSourceFile);

    stream << QString(
	"/* %1Plugin.cpp --- \n"
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
	"#include <QtDebug>\n"
	"\n"
	"#include \"%1.h\"\n"
	"#include \"%1Plugin.h\"\n"
	"\n"
	"// /////////////////////////////////////////////////////////////////\n"
	"// %1PluginPrivate\n"
	"// /////////////////////////////////////////////////////////////////\n"
	"\n"
	"class %1PluginPrivate \n"
	"{\n"
	"public:\n"
	"    // Class variables go here.\n"
	"};\n"
	"\n"
	"// /////////////////////////////////////////////////////////////////\n"
	"// %1Plugin\n"
	"// /////////////////////////////////////////////////////////////////\n"
	"\n"
	"%1Plugin::%1Plugin(QObject *parent) : dtkAbstractPlugin(parent), d(new %1PluginPrivate)\n"
	"{\n"
        "\n"
	"}\n"
	"\n"
	"%1Plugin::~%1Plugin(void)\n"
	"{\n"
        "    delete d;\n"
        "\n"
        "    d = NULL;\n"
	"}\n"
	"\n"
	"bool %1Plugin::initialize(void)\n"
	"{\n"
	"    if(!%1::registered())\n"
	"	qDebug() << \"Unable to register %1 type\";\n"
	"\n"
	"    return true;\n"
	"}\n"
	"\n"
	"bool %1Plugin::uninitialize(void)\n"
	"{\n"
	"    qDebug() << \"%1Plugin - uninitialize\";\n"
	"\n"
	"    return true;\n"
	"}\n"
	"\n"
	"QString %1Plugin::id(void) const\n"
	"{\n"
	"    return(\"%1Plugin\");\n"
	"}\n"
	"\n"
	"QString %1Plugin::url(void) const\n"
	"{\n"
	"    return(\"\");\n"
	"}\n"
	"\n"
	"QString %1Plugin::name(void) const\n"
	"{\n"
	"    return(\"%1Plugin\");\n"
	"}\n"
	"\n"
	"QPixmap %1Plugin::icon(void) const\n"
	"{\n"
	"    return(QPixmap());\n"
	"}\n"
	"\n"
	"QString %1Plugin::license(void) const\n"
	"{\n"
	"    return(\"\");\n"
	"}\n"
	"\n"
	"QString %1Plugin::version(void) const\n"
	"{\n"
	"    return(\"\");\n"
	"}\n"
	"\n"
	"QString %1Plugin::copyright(void) const\n"
	"{\n"
	"    return(\"\");\n"
	"}\n"
	"\n"
	"QString %1Plugin::description(void) const\n"
	"{\n"
	"    return(\"\");\n"
	"}\n"
	"\n"
	"QStringList %1Plugin::authors(void) const\n"
	"{\n"
	"    QStringList list;\n"
	"    list << \"\";\n"
	"    return(list);\n"
	"}\n"
	"\n"
	"QStringList %1Plugin::dependences(void) const\n"
	"{\n"
	"    return(QStringList());\n"
	"}\n"
	"\n"
	"QStringList %1Plugin::tags(void) const\n"
	"{\n"
	"    return(QStringList());\n"
	"}\n"
	"\n"
	)
	.arg(QString(d->plugin));

    pluginSourceFile.close();

    return true;
}
