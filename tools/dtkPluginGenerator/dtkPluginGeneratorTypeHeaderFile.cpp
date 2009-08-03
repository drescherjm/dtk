/* dtkPluginGeneratorTypeHeaderFile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar 10 10:45:27 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Aug  2 15:23:25 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPluginGenerator.h"

bool dtkPluginGenerator::generateTypeHeaderFile(void)
{
    QFile typeHeaderFile(d->target.absoluteFilePath(QString(d->plugin).append(".h")));

    if(!typeHeaderFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open" << QString(d->plugin).append(".h") << "for writing";
	return false;
    }
        
    QTextStream stream(&typeHeaderFile);

    stream << QString(
	"/* %1.h --- \n"
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
	"#ifndef %2_H\n"
	"#define %2_H\n"
	"\n"
	"#include <dtkCore/dtkGlobal.h>\n"
	"#include <dtkCore/dtkAbstract%3.h>\n"
	"\n"
	"#include \"%1PluginExport.h\"\n"
	"\n"
	"class %1Private;\n"
	"\n"
	"class %2PLUGIN_EXPORT %1 : public dtkAbstract%3\n"
	"{\n"
	"    Q_OBJECT\n"
	"\n"
	"public:\n"
	"             %1(void);\n"
	"    virtual ~%1(void);\n"
	"\n"
	"    virtual QString description(void) const;\n"
	)
	.arg(QString(d->plugin))
	.arg(QString(d->plugin).toUpper())
	.arg(QString(d->type));

    if(   QString(d->type).contains("DataReader")
       || QString(d->type).contains("DataWriter")
       || QString(d->type).contains("ViewAnimator")
       || QString(d->type).contains("ViewDecorator")
       || QString(d->type).contains("ViewInteractor")
       || QString(d->type).contains("ObjectInteractor")
       || QString(d->type).contains("WorldInteractor"))
   
	stream << QString(
	"    virtual QStringList handled(void) const;"
	    );

    stream << QString(
	"\n"
	"    static bool registered(void);\n"
	"\n"
	"private:\n"
	"    %1Private *d;"
	"};\n"
	"\n"
	"dtkAbstract%1 *create%2(void);\n"
	"\n"
	"#endif\n"
	"\n"
	)
	.arg(QString(d->type))
	.arg(QString(d->plugin).remove(d->prefix).prepend(QString(d->prefix).replace(0, 1, QString(d->prefix).left(1).toUpper())));

    typeHeaderFile.close();

    return true;
}
