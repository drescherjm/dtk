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

#include <QtCore>


class dtkCoreApplicationPrivate;

class DTKCORE_EXPORT dtkCoreApplication: public QCoreApplication
{
public:
             dtkCoreApplication(int &argc, char **argv);
    virtual ~dtkCoreApplication(void);

public:
    virtual void initialize(void);

    QCommandLineParser *parser(void) const ;
    QSettings        *settings(void) const ;

private:
    class dtkCoreApplicationPrivate *d;
};


