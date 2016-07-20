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

#include <QtWidgets>

#include "dtkWidgetsExport.h"

class DTKWIDGETS_EXPORT dtkSplitter : public QSplitter
{
    Q_OBJECT

public:
    dtkSplitter(QWidget *parent = 0, bool slim = true);
    ~dtkSplitter(void);

    QSplitterHandle *createHandle(void);

private:
    class dtkSplitterPrivate *d;
};

//
// dtkSplitter.h ends here
