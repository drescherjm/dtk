/* dtkApplication.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/02/04 12:01:21
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkWidgetsExport.h"
#include <dtkLog>

#include <QApplication>

class dtkApplicationPrivate;

class DTKWIDGETS_EXPORT dtkApplication: public QApplication
{
public:
    dtkApplication(int& argc, char **argv);
    virtual ~dtkApplication(void);

public:
    virtual void initialize(void);

public:
    virtual bool noGui(void);

public:
    static dtkApplication *create(int& argc, char *argv[]) {
        for (int i = 0; i < argc; i++)
            if (!qstrcmp(argv[i], "-nw") || !qstrcmp(argv[i], "--nw") ||  !qstrcmp(argv[i], "-no-window") || !qstrcmp(argv[i], "--no-window") || !qstrcmp(argv[i], "-h") || !qstrcmp(argv[i], "--help") || !qstrcmp(argv[i], "--version")) {
                qputenv("QT_QPA_PLATFORM", QByteArrayLiteral("minimal"));
            }

        return new dtkApplication(argc, argv);
    }

public:
    QCommandLineParser  *parser(void);
    QSettings         *settings(void);

protected:
    dtkApplicationPrivate *d;
};

