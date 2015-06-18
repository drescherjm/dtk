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

#include <QtWidgets>

class dtkComposerNodeRangeWidget : public QWidget
{
    Q_OBJECT

public:
     dtkComposerNodeRangeWidget(QWidget *parent = 0);
    ~dtkComposerNodeRangeWidget(void);

signals:
    void valueChanged(int);

public slots:
    void setMinValue(int);
    void setMaxValue(int);

private:
    QDial *m_dial;
};

class dtkComposerNodeRangeInspector : public QWidget
{
    Q_OBJECT

public:
     dtkComposerNodeRangeInspector(QWidget *parent = 0);
    ~dtkComposerNodeRangeInspector(void);

signals:
    void minValueChanged(int);
    void maxValueChanged(int);
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
