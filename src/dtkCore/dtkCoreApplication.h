/* dtkCoreApplication.h ---
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

#pragma once

#include "dtkCoreExport.h"

#include "dtkAbstractApplication.h"

#include <QtCore>


class dtkCoreApplicationPrivate;

class DTKCORE_EXPORT dtkCoreApplication: public QCoreApplication, public dtkAbstractApplication
{
public:
    dtkCoreApplication(int &argc, char **argv): QCoreApplication(argc, argv), dtkAbstractApplication() {};
    virtual ~dtkCoreApplication(void) {};

};


