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

#include <QtWidgets>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRangeWidget
// /////////////////////////////////////////////////////////////////

dtkComposerNodeRangeWidget::dtkComposerNodeRangeWidget(QWidget *parent) : QWidget(parent)
{
    QDial *dial = new QDial(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(dial);
}

dtkComposerNodeRangeWidget::~dtkComposerNodeRangeWidget(void)
{

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
