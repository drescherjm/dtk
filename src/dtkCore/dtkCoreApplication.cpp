/* dtkCoreApplication.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/01/26 12:24:18
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkCoreApplication.h"
#include <QtCore>

dtkCoreApplication::dtkCoreApplication(int &argc, char **argv): QCoreApplication(argc, argv), dtkAbstractApplication()
{
}

dtkCoreApplication::~dtkCoreApplication(void)
{
}

