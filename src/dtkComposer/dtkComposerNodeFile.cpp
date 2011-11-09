/* dtkComposerNodeFile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul  8 13:28:18 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Nov  9 11:18:09 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 217
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeFile_p.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>

#include <dtkGui/dtkTextEditor.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFilePrivate
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeFilePrivate::onRequestFinished(int id, bool error)
{
    if(id == this->dwnl_id)
        this->dwnl_ok = 1;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFile
// /////////////////////////////////////////////////////////////////

dtkComposerNodeFile::dtkComposerNodeFile(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeFilePrivate)
{
    d->property_output_file_name = new dtkComposerNodeProperty("name", dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, this);
    d->property_output_file_text = new dtkComposerNodeProperty("text", dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, this);
    d->property_output_file_url = new dtkComposerNodeProperty("url", dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, this);

    d->property_output_file_url->hide();

    this->setTitle("File");
    this->setKind(dtkComposerNode::Atomic);
    this->setType("dtkComposerFile");

    this->g->appendRightProperty(d->property_output_file_name);
    this->g->appendRightProperty(d->property_output_file_text);
    this->g->appendRightProperty(d->property_output_file_url);
    
    this->addAction("Choose file", this, SLOT(getFileName()));
    this->addAction("Setup url", this, SLOT(getUrl()));
    this->addAction("Edit file", this, SLOT(editFile()));

    d->dwnl_id = -1;
    d->dwnl_ok =  0;
}

dtkComposerNodeFile::~dtkComposerNodeFile(void)
{
    delete d;

    d = NULL;
}

QVariant dtkComposerNodeFile::value(dtkComposerNodeProperty *property)
{
    if(property == d->property_output_file_name) {
        return QVariant(d->file);
    }

    if(property == d->property_output_file_text) {
        return QVariant(dtkReadFile(d->file));
    }

    if(property == d->property_output_file_url) {
        return QVariant(d->url);
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
    dialog.setStyleSheet("background-color: none ; color: none;");
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec())
        d->file = dialog.selectedFiles().first();
}

void dtkComposerNodeFile::setFileName(const QString& file)
{
    d->file = file;
}

void dtkComposerNodeFile::getUrl(void)
{
    QInputDialog dialog(0);
    dialog.setStyleSheet("background-color: none ; color: none;");
    dialog.setLabelText("Url:");
    dialog.setTextValue(d->url.toString());
    if (dialog.exec())
        d->url = QUrl(dialog.textValue());
}

void dtkComposerNodeFile::setUrl(const QString& url)
{
    d->url = url;
}

void dtkComposerNodeFile::pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);    
}

void dtkComposerNodeFile::run(void)
{
    if (!d->url.isEmpty()) {

        QTemporaryFile file; file.setAutoRemove(false);
        
        if (!file.open()) {
            qDebug() << DTK_PRETTY_FUNCTION << "Unable to file for saving";
            return;
        }
        
        d->dwnl_ok = 0;

        QHttp http;
        
        connect(&http, SIGNAL(requestFinished(int, bool)), d, SLOT(onRequestFinished(int, bool)));

        http.setHost(d->url.host(), d->url.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp, d->url.port() == -1 ? 0 : d->url.port());
        
        if (!d->url.userName().isEmpty())
            http.setUser(d->url.userName(), d->url.password());
        
        QByteArray path = QUrl::toPercentEncoding(d->url.path(), "!$&'()*+,;=:@/");
        
        if (path.isEmpty()) {
            qDebug() << DTK_PRETTY_FUNCTION << "Invalid path" << d->url.path();
            return;
        }
        
        d->dwnl_id = http.get(path, &file);

        while(!d->dwnl_ok)
            qApp->processEvents();

        file.close();

        QFileInfo info(file);
        
        d->file = info.absoluteFilePath();
    }
    
    if (d->file.isEmpty())
        dtkDebug() << "File has not been initialized.";
    
    return;
}

void dtkComposerNodeFile::push(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property); 
}
