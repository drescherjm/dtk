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
    m_dial->setTracking(false);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_dial);

    connect(m_dial, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
    connect(m_dial, SIGNAL(rangeChanged(int, int)), this, SIGNAL(rangeChanged(int, int)));
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
    m_min = new QSpinBox(this); m_min->setKeyboardTracking(false);
    m_max = new QSpinBox(this); m_max->setKeyboardTracking(false);

    m_min->setRange(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max());
    m_max->setRange(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max());

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_min);
    layout->addWidget(m_max);
    layout->addStretch();

    connect(m_min, SIGNAL(valueChanged(int)), this, SIGNAL(minValueChanged(int)));
    connect(m_max, SIGNAL(valueChanged(int)), this, SIGNAL(maxValueChanged(int)));
}

dtkComposerNodeRangeInspector::~dtkComposerNodeRangeInspector(void)
{

}

void dtkComposerNodeRangeInspector::setRange(int min, int max)
{
    m_min->blockSignals(true);
    m_min->setValue(min);
    m_min->blockSignals(false);

    m_min->blockSignals(true);
    m_max->setValue(max);
    m_min->blockSignals(false);
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
    connect(m_widget, SIGNAL(rangeChanged(int, int)), m_inspector, SLOT(setRange(int, int)));

    m_widget->setMinValue(-10);
    m_widget->setMaxValue(10);
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

dtkComposerNodeRangePrivate::dtkComposerNodeRangePrivate(void) : widget(new dtkComposerNodeRangeViewWidget)
{ 
    connect(widget->widget(), SIGNAL(valueChanged(int)), this, SLOT(setValue(int))); 
}

void dtkComposerNodeRangePrivate::setValue(int v) 
{ 
    val = v; 
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRange
// /////////////////////////////////////////////////////////////////

dtkComposerNodeRange::dtkComposerNodeRange(void) : d(new dtkComposerNodeRangePrivate)
{
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
