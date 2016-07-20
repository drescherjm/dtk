// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include <QSplitter>

#include <dtkCoreSupport/dtkGlobal.h>

#include "dtkGuiSupportExport.h"

class dtkSplitterPrivate;

class DTKGUISUPPORT_EXPORT dtkSplitter : public QSplitter
{
    Q_OBJECT

public:
    dtkSplitter(QWidget *parent = 0, bool slim = true);
    ~dtkSplitter(void);

    QSplitterHandle *createHandle(void);

private:
    dtkSplitterPrivate *d;
};

//
// dtkSplitter.h ends here
