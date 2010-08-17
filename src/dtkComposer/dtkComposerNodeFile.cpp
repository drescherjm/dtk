/* dtkComposerNodeFile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul  8 13:28:18 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Aug 16 16:18:00 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 55
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

#include <dtkGui/dtkTextEditor.h>

#include <QtGui/QFileDialog>

class dtkComposerNodeFilePrivate
{
public:
    dtkComposerNodeProperty *property_output_file_name;
    dtkComposerNodeProperty *property_output_file_text;

public:
    QString file;
};

dtkComposerNodeFile::dtkComposerNodeFile(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeFilePrivate)
{
    d->property_output_file_name = new dtkComposerNodeProperty("name", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, this);
    d->property_output_file_text = new dtkComposerNodeProperty("text", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, this);

    this->setTitle("File");
    this->setKind(dtkComposerNode::Atomic);
    this->setType("dtkComposerFile");
    // this->addInputProperty(new dtkComposerNodeProperty("path", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, this));
    this->addOutputProperty(d->property_output_file_name);
    this->addOutputProperty(d->property_output_file_text);

    this->addAction("Choose file", this, SLOT(getFileName()));
    this->addAction("Edit file", this, SLOT(editFile()));
}

dtkComposerNodeFile::~dtkComposerNodeFile(void)
{
    delete d;

    d = NULL;
}

QVariant dtkComposerNodeFile::value(dtkComposerNodeProperty *property)
{
    if(property == d->property_output_file_name) {
        emit elapsed("00:00::000.001");
        emit progressed(QString("File name: %1").arg(d->file));
        emit progressed(100);
        return QVariant(d->file);
    }
}

void dtkComposerNodeFile::editFile(void)
{
    dtkTextEditor *editor = new dtkTextEditor;
    editor->open(d->file);
    editor->show();

    connect(editor, SIGNAL(closed()), editor, SLOT(deleteLater()));
}

void dtkComposerNodeFile::getFileName(void)
{
    d->file = QFileDialog::getOpenFileName(0, "File node");
}
