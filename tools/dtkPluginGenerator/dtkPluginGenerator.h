/* dtkPluginGenerator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar  9 21:40:22 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 11 19:41:27 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 23
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLUGINGENERATOR_H
#define DTKPLUGINGENERATOR_H

#include <QtCore>

class dtkPluginGeneratorPrivate
{
public:
    QString plugin;
    QString output;
    QString prefix;
    QString suffix;
    QString type;

    QDir parent;
    QDir target;
};

class dtkPluginGenerator
{
public:
    dtkPluginGenerator(void);
   ~dtkPluginGenerator(void);

   void setOutputDirectory(const QString& directory);
   void setPrefix(const QString& prefix);
   void setSuffix(const QString& suffix);
   void setType(const QString& type);

   bool run(void);

protected:
   bool generateCMakeLists(void);
   bool generateTypeHeaderFile(void);
   bool generateTypeSourceFile(void);
   bool generatePluginHeaderFile(void);
   bool generatePluginSourceFile(void);
   bool generateLoaderHeaderFile(void);
   bool generateLoaderSourceFile(void);
   bool generateExportHeaderFile(void);

private:
   dtkPluginGeneratorPrivate *d;
};

#endif
