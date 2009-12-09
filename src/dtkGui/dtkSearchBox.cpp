/* dtkSearchBox.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Dec  9 10:07:32 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec  9 10:22:23 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkGui/dtkSearchBox.h>

// /////////////////////////////////////////////////////////////////
// dtkSearchBoxPrivate
// /////////////////////////////////////////////////////////////////

class dtkSearchBoxPrivate
{
public:
    QLineEdit *edit;
    QPushButton *button;
};

// /////////////////////////////////////////////////////////////////
// dtkSearchBox
// /////////////////////////////////////////////////////////////////

dtkSearchBox::dtkSearchBox(QWidget *parent) : QWidget(parent), d(new dtkSearchBoxPrivate)
{
    d->edit = new QLineEdit(this);
    d->button = new QPushButton("Search", this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(2, 0, 0, 0);
    layout->setSpacing(5);
    layout->addWidget(d->edit);
    layout->addWidget(d->button);

    connect(d->edit, SIGNAL(returnPressed()), this, SLOT(onEnterPressed()));
    connect(d->edit, SIGNAL(textChanged(QString)), this, SIGNAL(textChanged(QString)));
    connect(d->button, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
}

dtkSearchBox::~dtkSearchBox(void)
{
    delete d;

    d = NULL;
}

QString dtkSearchBox::text(void) const
{
    return d->edit->text();
}

void dtkSearchBox::setText(const QString& text)
{
    d->edit->setText(text);
}

void dtkSearchBox::onButtonClicked(void)
{
    emit search(d->edit->text());
}

void dtkSearchBox::onEnterPressed(void)
{
    emit search(d->edit->text());
}
