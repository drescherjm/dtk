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

#include <QtWidgets>

#include <dtkCore/dtkGlobal.h>

#include "dtkGuiExport.h"

class dtkSplitterPrivate;

class DTKGUI_EXPORT dtkSplitter : public QSplitter
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
