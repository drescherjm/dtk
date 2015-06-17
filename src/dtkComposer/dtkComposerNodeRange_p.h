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

#include "dtkComposerViewWidget.h"

class dtkComposerNodeRangeWidget : public QWidget
{
    Q_OBJECT

public:
     dtkComposerNodeRangeWidget(QWidget *parent = 0);
    ~dtkComposerNodeRangeWidget(void);
};

class dtkComposerNodeRangeInspector : public QWidget
{
    Q_OBJECT

public:
     dtkComposerNodeRangeInspector(QWidget *parent = 0);
    ~dtkComposerNodeRangeInspector(void);
};

class dtkComposerNodeRangeViewWidget : public dtkComposerViewWidget
{
public:
     dtkComposerNodeRangeViewWidget(void);
    ~dtkComposerNodeRangeViewWidget(void);

public:
    QWidget *widget(void);
    QWidget *inspector(void);

public:
    dtkComposerNodeRangeWidget *m_widget;
    dtkComposerNodeRangeInspector *m_inspector;
};

//
// dtkComposerNodeRange_p.h ends here
