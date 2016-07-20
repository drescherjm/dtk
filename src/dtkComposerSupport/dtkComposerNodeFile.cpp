/* dtkComposerNodeFile.cpp ---
 *
 * Author: Julien Wintz, INRIA
 * Created: Thu Mar  1 11:45:03 2012 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeFile_p.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkWidgets/dtkNotification.h>

#include <QtCore>
#include <QtNetwork>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFilePrivate
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeFilePrivate::download(const QUrl& url)
{
    QFileInfo file_template_info = QFileInfo(url.path());

    if (!file_template_info.completeSuffix().isEmpty())
        this->file.setFileTemplate(file.fileTemplate() + "." + file_template_info.completeSuffix());

    this->file.setAutoRemove(false);

    if (!file.open()) {
        qDebug() << DTK_PRETTY_FUNCTION << "Unable to file for saving";
        return;
    }

    this->dwnl_ok = 0;

    QNetworkAccessManager http;

    connect(&http, SIGNAL(finished(QNetworkReply *)), this, SLOT(onRequestFinished(QNetworkReply *)));

    http.get(QNetworkRequest(url));

    while (!this->dwnl_ok)
        qApp->processEvents();

    this->file.close();

    QFileInfo info(this->file);

    this->tempName = info.absoluteFilePath();
}

void dtkComposerNodeFilePrivate::onRequestFinished(QNetworkReply *reply)
{
    this->file.write(reply->readAll());
    this->file.flush();
    this->dwnl_ok = 1;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFile implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeFile::dtkComposerNodeFile(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeFilePrivate)
{
    this->appendReceiver(&(d->receiver));

    d->fileName = QString();
    d->emitter.setData(&d->fileName);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeFile::~dtkComposerNodeFile(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeFile::run(void)
{
    QString path;

    if (!d->receiver.isEmpty())
        path = *d->receiver.data();
    else
        path = d->fileName;

    if (path.startsWith("http")) {

        d->download(QUrl(path));

        if (!d->tempName.isEmpty())
            d->fileName = d->tempName;
        else
            d->fileName = path;

    } else {

        d->fileName = path;

    }

    if (!QFile(d->fileName).exists()) {
        QString msg = QString("File %1 does not exist! ").arg(d->fileName);
        dtkNotify(msg, 30000);
    }
}

QString dtkComposerNodeFile::type(void)
{
    return "file";
}

QString dtkComposerNodeFile::titleHint(void)
{
    return "File";
}

QString dtkComposerNodeFile::inputLabelHint(int port)
{
    if (port == 0)
        return "name";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeFile::outputLabelHint(int port)
{
    if (port == 0)
        return "file";

    return dtkComposerNode::outputLabelHint(port);
}

QString dtkComposerNodeFile::value(void)
{
    return d->fileName;
}

void dtkComposerNodeFile::setValue(QString value)
{
    value.replace("~", QDir::homePath());
    d->fileName = value;
}



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFileExists implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeFileExists::dtkComposerNodeFileExists(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeFileExistsPrivate)
{
    this->appendReceiver(&(d->receiver));

    d->exists = false;
    d->emitter.setData(&d->exists);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeFileExists::~dtkComposerNodeFileExists(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeFileExists::run(void)
{
    if (!d->receiver.isEmpty()) {
        if (d->receiver.data()) {
            QString filename = *(d->receiver.data());
            d->exists = QFile(filename).exists();
        }
    }
}

QString dtkComposerNodeFileExists::type(void)
{
    return "fileExists";
}

QString dtkComposerNodeFileExists::titleHint(void)
{
    return "FileExists";
}

QString dtkComposerNodeFileExists::inputLabelHint(int port)
{
    if (port == 0)
        return "file";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeFileExists::outputLabelHint(int port)
{
    if (port == 0)
        return "exists";

    return dtkComposerNode::outputLabelHint(port);
}




// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFileList implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeFileList::dtkComposerNodeFileList(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeFileListPrivate)
{
    this->appendReceiver(&(d->receiver_dir));
    QList<int> variant_list;
    variant_list << QMetaType::QString << QMetaType::QStringList;
    d->receiver_filters.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_filters));

    d->emitter_files.setData(&(d->files));
    this->appendEmitter(&(d->emitter_files));
}

dtkComposerNodeFileList::~dtkComposerNodeFileList(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeFileList::run(void)
{
    if (!d->receiver_dir.isEmpty()) {

        d->files.clear();

        if (d->receiver_dir.data()) {

            QString dirname = *(d->receiver_dir.data());
            QDir dir(dirname);

            if (!d->receiver_filters.isEmpty()) {

                switch (d->receiver_filters.dataType()) {

                case QMetaType::QString: {
                    dir.setNameFilters(QStringList(*(d->receiver_filters.data<QString>())));
                    break;
                }

                case QMetaType::QStringList: {
                    dir.setNameFilters(*(d->receiver_filters.data<QStringList>()));
                    break;
                }

                default:
                    dtkWarn() << "Type" << d->receiver_filters.dataType() << "is not handled by the node. Only QString and QString List are supported";
                    break;
                }
            }

            foreach (QFileInfo file, dir.entryInfoList()) {
                d->files << file.absoluteFilePath();
            }

        }
    }
}

QString dtkComposerNodeFileList::type(void)
{
    return "fileList";
}

QString dtkComposerNodeFileList::titleHint(void)
{
    return "FileList";
}

QString dtkComposerNodeFileList::inputLabelHint(int port)
{
    if (port == 0)
        return "directory";

    if (port == 1)
        return "pattern";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeFileList::outputLabelHint(int port)
{
    if (port == 0)
        return "files";

    return dtkComposerNode::outputLabelHint(port);
}






// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFileRead implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeFileRead::dtkComposerNodeFileRead(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeFileReadPrivate)
{
    this->appendReceiver(&(d->receiver_file));

    d->emitter.setData(&(d->data));
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeFileRead::~dtkComposerNodeFileRead(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeFileRead::run(void)
{
    QString filename;

    if (!d->receiver_file.isEmpty()) {
        filename = *(d->receiver_file.data());

        if (!filename.isEmpty()) {
            QFile file(filename);

            if (!file.open(QIODevice::ReadOnly)) return;

            d->data = file.readAll();
        }
    }
}

QString dtkComposerNodeFileRead::type(void)
{
    return "fileRead";
}

QString dtkComposerNodeFileRead::titleHint(void)
{
    return "FileRead";
}

QString dtkComposerNodeFileRead::inputLabelHint(int port)
{
    if (port == 0)
        return "file";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeFileRead::outputLabelHint(int port)
{
    if (port == 0)
        return "bytes";

    return dtkComposerNode::outputLabelHint(port);
}



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFileWrite implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeFileWrite::dtkComposerNodeFileWrite(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeFileWritePrivate)
{
    this->appendReceiver(&(d->receiver_data));
    this->appendReceiver(&(d->receiver_file));

    d->success = false;
    d->emitter.setData(&(d->success));
    this->appendEmitter(&(d->emitter));
    d->emitter_file.setData(&(d->filename));
    this->appendEmitter(&(d->emitter_file));
}

dtkComposerNodeFileWrite::~dtkComposerNodeFileWrite(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeFileWrite::run(void)
{
    d->success = false;

    if (!d->receiver_file.isEmpty() && !d->receiver_data.isEmpty()) {
        d->filename = *(d->receiver_file.data());

        if (!d->filename.isEmpty()) {
            QFile file(d->filename);

            if (!file.open(QIODevice::WriteOnly)) {
                dtkError() << "Can't open file for writing" << d->filename;
                return;
            }

            qlonglong size = file.write(*(d->receiver_data.data()));

            if (size < 0) {
                dtkWarn() << "error while writing to file" << d->filename << file.errorString();
                return;
            }

            d->success = file.flush();
            file.close();
            //we should use QSaveFile, but only available in Qt 5.1.
        } else {
            dtkWarn() << Q_FUNC_INFO << "file name is empty";
        }

    } else {
        dtkWarn() << Q_FUNC_INFO << "The input are not all set. Nothing is done.";
    }
}

QString dtkComposerNodeFileWrite::type(void)
{
    return "fileWrite";
}

QString dtkComposerNodeFileWrite::titleHint(void)
{
    return "FileWrite";
}

QString dtkComposerNodeFileWrite::inputLabelHint(int port)
{
    if (port == 0)
        return "bytes";

    if (port == 1)
        return "file";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeFileWrite::outputLabelHint(int port)
{
    if (port == 0)
        return "success";

    if (port == 1)
        return "file";

    return dtkComposerNode::inputLabelHint(port);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeDirectory implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeDirectory::dtkComposerNodeDirectory(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeDirectoryPrivate)
{
    this->appendReceiver(&(d->receiver_directory));

    d->emitter_directory.setData(&(d->directory));
    this->appendEmitter(&(d->emitter_directory));
}

dtkComposerNodeDirectory::~dtkComposerNodeDirectory(void)
{
    delete d;
    d = NULL;
}

void dtkComposerNodeDirectory::run(void)
{
    QString directory;

    if (!d->receiver_directory.isEmpty()) {
        directory = *d->receiver_directory.data();
    } else {
        directory = d->directory;
    }

    d->directory = directory;

    if (!QDir(d->directory).exists()) {
        QString msg = QString("Directory %1 does not exist! ").arg(d->directory);
        dtkNotify(msg, 30000);
    }
}

QString dtkComposerNodeDirectory::type(void)
{
    return "directory";
}

QString dtkComposerNodeDirectory::titleHint(void)
{
    return "Directory";
}

QString dtkComposerNodeDirectory::inputLabelHint(int port)
{
    if (port == 0)
        return "dir";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeDirectory::outputLabelHint(int port)
{
    if (port == 0)
        return "dir";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeDirectory::value(void)
{
    return d->directory;
}

void dtkComposerNodeDirectory::setValue(QString value)
{
    value.replace("~", QDir::homePath());
    d->directory = value;
}
