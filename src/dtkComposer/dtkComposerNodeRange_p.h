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
#include "dtkComposerTransmitterEmitter.h"

#include <QtWidgets>

class dtkComposerNodeRangeWidget : public QWidget
{
    Q_OBJECT

public:
     dtkComposerNodeRangeWidget(QWidget *parent = 0);
    ~dtkComposerNodeRangeWidget(void);

signals:
    void valueChanged(int);
    void rangeChanged(int, int);

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

public slots:
    void setRange(int, int);

public:
    QSpinBox *m_min;
    QSpinBox *m_max;
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

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRangePrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRangePrivate : public QObject
{
    Q_OBJECT

public:
     dtkComposerNodeRangePrivate(void);

public:
    dtkComposerTransmitterEmitter<qlonglong> emt_val;

public:
    qlonglong min;
    qlonglong max;
    qlonglong val;

public:
    dtkComposerNodeRangeViewWidget *widget;

public slots:
    void setValue(int);
};

//
// dtkComposerNodeRange_p.h ends here
