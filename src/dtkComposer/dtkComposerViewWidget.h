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

#include "dtkComposerExport.h"

#include <QtWidgets>

class DTKCOMPOSER_EXPORT dtkComposerViewWidget : public QWidget
{
    Q_OBJECT

public:
     dtkComposerViewWidget(void);
    ~dtkComposerViewWidget(void);

signals:
    void   focused(void);
    void unfocused(void);

public:
    virtual QWidget *widget(void);
    virtual QWidget *inspector(void);

private:
    class dtkComposerViewWidgetPrivate *d;
};

//
// dtkComposerViewWidget.h ends here
