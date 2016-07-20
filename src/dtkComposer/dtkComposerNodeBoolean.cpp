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

#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeBoolean_p.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanEditor implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeBooleanEditor::dtkComposerNodeBooleanEditor(dtkComposerNodeBooleanPrivate *d_ptr) : QFrame(), d(d_ptr)
{
    f_b = new QRadioButton("false", this);
    t_b = new QRadioButton( "true", this);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(t_b);
    layout->addWidget(f_b);

    this->setLayout(layout);

    QButtonGroup *g_b = new QButtonGroup(this);
    g_b->setExclusive(true);
    g_b->addButton(t_b);
    g_b->addButton(f_b);

    connect(t_b, SIGNAL(toggled(bool)), this, SLOT(onValueChanged(bool)));
}

void dtkComposerNodeBooleanEditor::refresh(void)
{
    t_b->blockSignals(true);
    f_b->blockSignals(true);

    if (d->value) {
        t_b->setChecked(true);
        f_b->setChecked(false);

    } else {
        t_b->setChecked(false);
        f_b->setChecked(true);
    }

    t_b->blockSignals(false);
    f_b->blockSignals(false);
}

void dtkComposerNodeBooleanEditor::onValueChanged(bool val)
{
    d->value = val;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanPrivate implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeBooleanEditor *dtkComposerNodeBooleanPrivate::editor(void)
{
    if (!m_editor)
        m_editor = new dtkComposerNodeBooleanEditor(this);

    m_editor->refresh();

    return m_editor;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBoolean implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeBoolean::dtkComposerNodeBoolean(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeBooleanPrivate)
{
    this->appendReceiver(&d->receiver);
    this->appendEmitter(&d->emitter);

    d->value = false;
    d->m_editor = NULL;
}

dtkComposerNodeBoolean::~dtkComposerNodeBoolean(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeBoolean::run(void)
{
    if (!d->receiver.isEmpty())
        d->value = (d->receiver.data());

    d->emitter.setData(d->value);
}

bool dtkComposerNodeBoolean::value(void)
{
    return d->value;
}

void dtkComposerNodeBoolean::setValue(bool value)
{
    d->value = value;
}

dtkComposerNodeBooleanEditor *dtkComposerNodeBoolean::editor(void)
{
    return d->editor();
}

//
// dtkComposerNodeBoolean.cpp ends here
