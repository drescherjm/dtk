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

#include "dtkComposerNodeRange.h"
#include "dtkComposerNodeRange_p.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRangeWidget
// /////////////////////////////////////////////////////////////////

dtkComposerNodeRangeWidget::dtkComposerNodeRangeWidget(QWidget *parent) : QWidget(parent)
{
    m_dial = new QDial(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_dial);

    connect(m_dial, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
}

dtkComposerNodeRangeWidget::~dtkComposerNodeRangeWidget(void)
{

}

void dtkComposerNodeRangeWidget::setMinValue(int value)
{
    m_dial->setMinimum(value);
}

void dtkComposerNodeRangeWidget::setMaxValue(int value)
{
    m_dial->setMaximum(value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRangeInspector
// /////////////////////////////////////////////////////////////////

dtkComposerNodeRangeInspector::dtkComposerNodeRangeInspector(QWidget *parent) : QWidget(parent)
{
    QSpinBox *min = new QSpinBox(this);
    QSpinBox *max = new QSpinBox(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(min);
    layout->addWidget(max);
    layout->addStretch();

    connect(min, SIGNAL(valueChanged(int)), this, SIGNAL(minValueChanged(int)));
    connect(max, SIGNAL(valueChanged(int)), this, SIGNAL(maxValueChanged(int)));
}

dtkComposerNodeRangeInspector::~dtkComposerNodeRangeInspector(void)
{

}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRangeViewWidget
// /////////////////////////////////////////////////////////////////

dtkComposerNodeRangeViewWidget::dtkComposerNodeRangeViewWidget(void)
{
    m_widget = new dtkComposerNodeRangeWidget;
    m_inspector = new dtkComposerNodeRangeInspector;

    connect(m_inspector, SIGNAL(minValueChanged(int)), m_widget, SLOT(setMinValue(int)));
    connect(m_inspector, SIGNAL(maxValueChanged(int)), m_widget, SLOT(setMaxValue(int)));
}

dtkComposerNodeRangeViewWidget::~dtkComposerNodeRangeViewWidget(void)
{
    delete m_widget;
    delete m_inspector;
}

QWidget *dtkComposerNodeRangeViewWidget::widget(void)
{
    return m_widget;
}

QWidget *dtkComposerNodeRangeViewWidget::inspector(void)
{
    return m_inspector;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRangePrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRangePrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emt_val;

public:
    qlonglong min;
    qlonglong max;
    qlonglong val;

public:
    dtkComposerNodeRangeViewWidget *widget;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRange
// /////////////////////////////////////////////////////////////////

dtkComposerNodeRange::dtkComposerNodeRange(void)
{
    d = new dtkComposerNodeRangePrivate;
    d->widget = new dtkComposerNodeRangeViewWidget;

    this->appendEmitter(&d->emt_val);
}

dtkComposerNodeRange::~dtkComposerNodeRange(void)
{
    delete d;
}

void dtkComposerNodeRange::setValue(int value)
{
    d->val = value;
}

void dtkComposerNodeRange::run(void)
{
    d->emt_val.setData(d->val);
}

dtkComposerViewWidget *dtkComposerNodeRange::widget(void)
{
    return d->widget;
}

//
// dtkComposerNodeRange.cpp ends here
