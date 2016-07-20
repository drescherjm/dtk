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

#include <QWidget>

#include "dtkWidgetsExport.h"

class DTKWIDGETS_EXPORT dtkSpacer : public QWidget
{
    Q_OBJECT

public:
    dtkSpacer(QWidget *parent = 0, int width = 0, int height = 0);
    ~dtkSpacer(void);

    QSize sizeHint (void) const;
};

//
// dtkSpacer.h ends here
