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

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <QtWidgets>

class dtkComposerNodeBooleanPrivate;

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanEditor : public QFrame
{
    Q_OBJECT

public:
    dtkComposerNodeBooleanEditor(dtkComposerNodeBooleanPrivate *d_ptr);

public:
    void refresh(void);

public slots:
    void onValueChanged(bool);

public:
    QRadioButton *f_b;
    QRadioButton *t_b;

public:
    dtkComposerNodeBooleanPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanPrivate
{
public:
    dtkComposerTransmitterReceiver<bool> receiver;

public:
    dtkComposerTransmitterEmitter<bool> emitter;

public:
    bool value;

public:
    dtkComposerNodeBooleanEditor *m_editor;

public:
    dtkComposerNodeBooleanEditor *editor(void);
};

//
// dtkComposerNodeBoolean_p.h ends here
