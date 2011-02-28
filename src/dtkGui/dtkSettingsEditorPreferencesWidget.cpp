/* dtkSettingsEditorPreferencesWidget.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Dec 23 10:34:54 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec 23 10:50:29 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkSettingsEditor.h"
#include "dtkSettingsEditorPreferencesWidget.h"

class dtkSettingsEditorPreferencesWidgetPrivate
{
public:
    dtkSettingsEditor *editor;

    QDialogButtonBox *box;
};

dtkSettingsEditorPreferencesWidget::dtkSettingsEditorPreferencesWidget(QWidget *parent) : dtkPreferencesPage(parent), d(new dtkSettingsEditorPreferencesWidgetPrivate)
{
    d->editor = new dtkSettingsEditor(this);
    d->editor->setSettings("inria", "dtk");

    d->box = new QDialogButtonBox(this);
    d->box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(d->box, SIGNAL(accepted()), this, SIGNAL(accepted()));
    connect(d->box, SIGNAL(rejected()), this, SIGNAL(rejected()));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(d->editor);
    layout->addWidget(d->box);
}

dtkSettingsEditorPreferencesWidget::~dtkSettingsEditorPreferencesWidget(void)
{
    delete d;
    d = NULL;
}
