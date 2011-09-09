/* dtkComposerNodeFile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul  8 13:28:18 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Aug 30 10:52:37 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 94
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
#include <dtkCore/dtkLog.h>

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

    this->addOutputProperty(d->property_output_file_name);
    this->addOutputProperty(d->property_output_file_text);
    
    this->addAction("Choose file", this, SLOT(getFileName()));
    this->addAction("Edit file", this, SLOT(editFile()));

    d->file = QString();
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

    return QVariant();
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
    QFileDialog dialog(0, tr("Choose file"));
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec())
        d->file = dialog.selectedFiles().first();    

    //d->file = QFileDialog::getOpenFileName(0, tr("Choose file"));
}

void dtkComposerNodeFile::setFileName(const QString& file)
{
    d->file = file;
}

void dtkComposerNodeFile::pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);    
}

void dtkComposerNodeFile::run(void)
{
    if (d->file.isEmpty())
        dtkDebug() << "File has not been initialized.";

    return;
}

void dtkComposerNodeFile::push(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property); 
}
