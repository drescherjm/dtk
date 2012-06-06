/* dtkTestGenerator.h ---
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar  9 21:40:22 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Sep  5 14:53:38 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 31
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef dtkTestGenerator_H
#define dtkTestGenerator_H

#include <QtCore>

class dtkTestGeneratorPrivate
{
public:
    QString classTestName;
    QString className;
    QString output;
    QString useGui;

    QDir parent;
    QDir target;
};

class dtkTestGenerator
{
public:
    dtkTestGenerator(void);
   ~dtkTestGenerator(void);

   void setOutputDirectory(const QString& directory);
   void setClassName(const QString& prefix);
   void setUseGui(bool useGui);
   
   bool run(void);

protected:
   bool generateCMakeLists(void);
   bool generateTestHeaderFile(void);
   bool generateTestSourceFile(void);

private:
   dtkTestGeneratorPrivate *d;
};

#endif
