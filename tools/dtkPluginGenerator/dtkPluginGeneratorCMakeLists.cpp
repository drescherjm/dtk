/* dtkPluginGeneratorCMakeLists.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar 10 10:18:39 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jun 29 18:53:55 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 15
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPluginGenerator.h"

bool dtkPluginGenerator::generateCMakeLists(void)
{
    QFile cmakeFile(d->target.absoluteFilePath("CMakeLists.txt"));

    if(!cmakeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qWarning() << "dtkPluginGenerator: unable to open CMakeLists.txt for writing";
	return false;
    }
        
    QTextStream stream(&cmakeFile);

    stream << QString(
	"### CMakeLists.txt --- \n"
	"## \n"
	"## Author:\n"
	"## Copyright (C)\n"
	"## Created:\n"
	"## Version:\n"
	"## Last-Updated:\n"
	"##           By:\n"
	"##     Update #:\n"
	"######################################################################\n"
	"## \n"
	"### Commentary: \n"
	"## \n"
	"######################################################################\n"
	"## \n"
	"### Change log:\n"
	"## \n"
	"######################################################################\n"
	"\n"
	"project(%1Plugin)\n"
	"\n"
	"set(${PROJECT_NAME}_HEADERS\n"
	"  %1Plugin.h\n"
	"  %1.h\n"
	")\n"
	"\n"
	"set(${PROJECT_NAME}_SOURCES\n"
	"  %1Plugin.cpp\n"
	"  %1PluginLoader.cpp\n"
	"  %1.cpp\n"
	")\n"
	"\n"
	"## #################################################################\n"
	"## Build rules\n"
	"## #################################################################\n"
	"\n"
	"qt4_wrap_cpp(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS})\n"
	"\n"
	"add_library(${PROJECT_NAME} SHARED\n"
	"  ${${PROJECT_NAME}_SOURCES} \n"
	"  ${${PROJECT_NAME}_HEADERS}\n"
	"  ${${PROJECT_NAME}_HEADERS_MOC}\n"
	")\n"
	"\n"
	"# target_link_libraries(${PROJECT_NAME}\n"
	"# \n"
	"# )\n"
	"\n"
	"if(APPLE)\n"
	"  set(CMAKE_SHARED_LINKER_FLAGS \"-undefined dynamic_lookup\")\n"
	"elseif(UNIX)\n"
	"  string(REPLACE \"-Wl,--no-undefined\" \"\" CMAKE_SHARED_LINKER_FLAGS \"${CMAKE_SHARED_LINKER_FLAGS}\")\n"
	"endif()\n"
	"\n"
	)
	.arg(QString(d->plugin));

    cmakeFile.close();

    return true;
}
