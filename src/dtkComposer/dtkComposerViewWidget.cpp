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

#include "dtkComposerViewWidget.h"

class dtkComposerViewWidgetPrivate
{
public:

};

dtkComposerViewWidget::dtkComposerViewWidget(void)
{
    d = new dtkComposerViewWidgetPrivate;
}

dtkComposerViewWidget::~dtkComposerViewWidget(void)
{
    delete d;
}

QWidget *dtkComposerViewWidget::widget(void)
{
    return NULL;
}

QWidget *dtkComposerViewWidget::inspector(void)
{
    return NULL;
}

//
// dtkComposerViewWidget.cpp ends here
