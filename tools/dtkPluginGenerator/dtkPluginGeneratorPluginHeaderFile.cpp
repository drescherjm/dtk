/* dtkPluginGeneratorPluginHeaderFile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Mar 11 14:22:17 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Aug  2 15:22:22 2009 (+0200)
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

bool dtkPluginGenerator::generatePluginHeaderFile(void)
{
    QFile pluginHeaderFile(d->target.absoluteFilePath(QString(d->plugin).append("Plugin.h")));

    if(!pluginHeaderFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open" << QString(d->plugin).append("Plugin.h") << "for writing";
	return false;
    }
        
    QTextStream stream(&pluginHeaderFile);

    stream << QString(
	"/* %1Plugin.h --- \n"
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
	"#ifndef %2PLUGIN_H\n"
	"#define %2PLUGIN_H\n"
	"\n"
	"#include <dtkCore/dtkGlobal.h>\n"
	"#include <dtkCore/dtkAbstractPlugin.h>\n"
	"\n"
	"#include \"%1PluginExport.h\"\n"
	"\n"
	"class %2PLUGIN_EXPORT %1PluginPrivate;\n"
	"\n"
	"class %2PLUGIN_EXPORT %1Plugin : public dtkAbstractPlugin\n"
	"{\n"
	"    Q_OBJECT\n"
	"\n"
	"public:\n"
	"     %1Plugin(QObject *parent = 0);\n"
	"    ~%1Plugin(void);\n"
	"\n"
	"    virtual bool initialize(void);\n"
	"    virtual bool uninitialize(void);\n"
	"\n"
	"    virtual QString id(void) const;\n"
	"    virtual QString url(void) const;\n"
	"    virtual QPixmap icon(void) const;\n"
	"    virtual QString name(void) const;\n"
	"    virtual QString license(void) const;\n"
	"    virtual QString version(void) const;\n"
	"    virtual QString copyright(void) const;\n"
	"    virtual QStringList authors(void) const;\n"
	"    virtual QString description(void) const;\n"
	"    virtual QStringList dependences(void) const;\n"
	"    virtual QStringList tags(void) const;\n"
        "\n"
	"private:\n"
	"     %1PluginPrivate *d;\n"
	"};\n"
	"\n"
	"#endif\n"
	"\n"
	)
	.arg(QString(d->plugin))
	.arg(QString(d->plugin).toUpper());

    pluginHeaderFile.close();

    return true;
}
