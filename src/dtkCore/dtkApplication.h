/* dtkApplication.h ---
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

#include "dtkBaseApplication.h"
#include "dtkCoreApplication.h"

#include <QApplication>

class DTKCORE_EXPORT dtkApplication: public QApplication, public dtkBaseApplication
{
public:
             dtkApplication(int &argc, char **argv): QApplication(argc, argv), dtkBaseApplication() {};
    virtual ~dtkApplication(void);

};

static QCoreApplication* create(int &argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
        if(!qstrcmp(argv[i], "-nw") || !qstrcmp(argv[i], "-no-window"))
            return new dtkCoreApplication(argc, argv);

    return new dtkApplication(argc, argv);

}

