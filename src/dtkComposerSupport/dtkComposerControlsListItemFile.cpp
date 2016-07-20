/* @(#)dtkComposerControlsListItemFile.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/06/03 12:35:31
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerControlsListItemFile.h"

#include "dtkComposerNodeFile.h"

#include "dtkComposerSupportExport.h"
#include <dtkCoreSupport/dtkGlobal.h>

class dtkComposerControlsListItemFilePrivate
{
public:
    QListWidget *parent;

public:
    dtkComposerSceneNode *node;

public:
    dtkComposerNodeFile *s_node;

public:
    QLineEdit     *edit;
    QToolButton *butn_f;
};

dtkComposerControlsListItemFile::dtkComposerControlsListItemFile(QListWidget *parent, dtkComposerSceneNode *node) : dtkComposerControlsListItem(parent, node), d(new dtkComposerControlsListItemFilePrivate)
{
    d->node = node;

    if (dtkComposerNodeFile *s_node = dynamic_cast<dtkComposerNodeFile *>(d->node->wrapee()))
        d->s_node = s_node;
    else
        dtkError() << "Not a file node, can't create control list item";

    d->parent = parent;
}

dtkComposerControlsListItemFile::~dtkComposerControlsListItemFile(void )
{
    delete d;
    d = NULL;
}

QWidget *dtkComposerControlsListItemFile::widget(void)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    QFrame *frame = new QFrame(d->parent);
    frame->setLayout(layout);
    layout->addWidget(new QLabel(d->node->title(), frame));

    d->edit  = new QLineEdit(frame);
    d->edit->setText(d->s_node->value());

    d->butn_f = new QToolButton(frame);
    d->butn_f->setText("Browse");

    QObject::connect(d->edit, SIGNAL(textChanged(QString)), this, SLOT(onValueChanged(QString)));
    QObject::connect(d->butn_f, SIGNAL(clicked()), this, SLOT(onBrowse()));

    layout->addWidget(d->edit);
    layout->addWidget(d->butn_f);
    return frame;
}

void dtkComposerControlsListItemFile::onBrowse(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("composer");
    QString path = settings.value("last_open_file_node", QDir::homePath()).toString();
    settings.endGroup();

    QFileDialog *dialog = new QFileDialog(0, tr("Open file"), path);
    dialog->setStyleSheet("background-color: none ; color: none;");
    dialog->setAcceptMode(QFileDialog::AcceptOpen);
    dialog->setFileMode(QFileDialog::AnyFile);
    dialog->open(this, SLOT(onBrowse(const QString&)));
}


void dtkComposerControlsListItemFile::onBrowse(const QString& file)
{
    QFileInfo info(file);

    QSettings settings("inria", "dtk");
    settings.beginGroup("composer");
    settings.setValue("last_open_file_node", info.absolutePath());
    settings.endGroup();

    d->edit->setText(file);
}


void dtkComposerControlsListItemFile::onValueChanged(const QString& value)
{
    d->s_node->setValue(value);
}


