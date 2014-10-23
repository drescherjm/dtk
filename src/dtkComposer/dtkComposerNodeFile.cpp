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

#include <dtkGuiSupport/dtkNotification.h>

#include <QtCore>
#include <QtNetwork>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFilePrivate
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeFilePrivate::download(const QUrl& url)
{
    Q_UNUSED(url);

    // QFileInfo file_template_info = QFileInfo(url.path());

    // QTemporaryFile file;
    // if(!file_template_info.completeSuffix().isEmpty())
    //     file.setFileTemplate(file.fileTemplate() + "." + file_template_info.completeSuffix());
    // file.setAutoRemove(false);
    
    // if (!file.open()) {
    //     qDebug() << Q_FUNC_INFO << "Unable to file for saving";
    //     return;
    // }
        
    // this->dwnl_ok = 0;
    
    // QHttp http;
    
    // connect(&http, SIGNAL(requestFinished(int, bool)), this, SLOT(onRequestFinished(int, bool)));

    // http.setHost(url.host(), url.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp, url.port() == -1 ? 0 : url.port());
        
    // if (!url.userName().isEmpty())
    //     http.setUser(url.userName(), url.password());
        
    // QByteArray path = QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/");
    
    // if (path.isEmpty()) {
    //     qDebug() << Q_FUNC_INFO << "Invalid path" << url.path();
    //     return;
    // }
    
    // this->dwnl_id = http.get(path, &file);
    
    // while(!this->dwnl_ok)
    //     qApp->processEvents();

    // file.close();

    // QFileInfo info(file);
    
    // this->tempName = info.absoluteFilePath();
}

void dtkComposerNodeFilePrivate::onRequestFinished(int id, bool error)
{
    Q_UNUSED(error);

    if(id == this->dwnl_id)
        this->dwnl_ok = 1;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFile implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeFile::dtkComposerNodeFile(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeFilePrivate)
{
    this->appendReceiver(&(d->receiver));

    d->fileName = QString();
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
        path = d->receiver.data();
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
        dtkNotify(msg,30000);
    }

    d->emitter.setData(d->fileName);
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
    if(port == 0)
        return "name";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeFile::outputLabelHint(int port)
{
    if(port == 0)
        return "file";

    return dtkComposerNode::outputLabelHint(port);
}

QString dtkComposerNodeFile::value(void)
{
    return d->fileName;
}

void dtkComposerNodeFile::setValue(QString value)
{
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
        QString filename = d->receiver.data();
        d->exists = QFile(filename).exists();
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
    if(port == 0)
        return "file";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeFileExists::outputLabelHint(int port)
{
    if(port == 0)
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
    d->receiver_filters.setTypeList(variant_list);
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


        QString dirname = d->receiver_dir.data();
        QDir dir(dirname);

        if (!d->receiver_filters.isEmpty()) {

            switch(d->receiver_filters.variant().type()) {

            case QMetaType::QString: {
                dir.setNameFilters(QStringList(d->receiver_filters.data<QString>()));
                break;
            }

            case QMetaType::QStringList: {
                dir.setNameFilters(d->receiver_filters.data<QStringList>());
                break;
            }

            default:
                dtkWarn() << "Type" << d->receiver_filters.variant().type() << "is not handled by the node. Only QString and QString List are supported";
                break;
            }
        }

        foreach (QFileInfo file, dir.entryInfoList()) {
            d->files << file.absoluteFilePath();
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
    if(port == 0)
        return "directory";
    if(port == 1)
        return "pattern";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeFileList::outputLabelHint(int port)
{
    if(port == 0)
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

    if(!d->receiver_file.isEmpty()) {
        filename = d->receiver_file.data();

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
    if(port == 0)
        return "file";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeFileRead::outputLabelHint(int port)
{
    if(port == 0)
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
    this->appendEmitter(&(d->emitter));
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
    if(!d->receiver_file.isEmpty() && !d->receiver_data.isEmpty()) {
         d->filename = d->receiver_file.data();
         d->emitter_file.setData(d->filename);

        if (!d->filename.isEmpty()) {
            QFile file(d->filename);

            if(!file.open(QIODevice::WriteOnly)) {
                dtkError() << "Can't open file for writing"<< d->filename;
                return;
            }

            qlonglong size = file.write(*(d->receiver_data.data()));
            if (size < 0) {
                dtkWarn() << "error while writing to file" << d->filename << file.errorString();
                return;
            }
            d->success = file.flush();
            d->emitter.setData(d->success);
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
    if(port == 0)
        return "bytes";
    if(port == 1)
        return "file";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeFileWrite::outputLabelHint(int port)
{
    if(port == 0)
        return "success";
    if(port == 1)
        return "file";

    return dtkComposerNode::inputLabelHint(port);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeDirectory implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeDirectory::dtkComposerNodeDirectory(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeDirectoryPrivate)
{
    this->appendReceiver(&(d->receiver_directory));

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
        directory = d->receiver_directory.data();
    }
    else {
        directory = d->directory;
    }

    d->directory = directory;
    d->emitter_directory.setData(d->directory);

    dtkDebug()<<"DIRECTORY : "<<d->directory;

    if (!QDir(d->directory).exists()) {
        QString msg = QString("Directory %1 does not exist! ").arg(d->directory);
        dtkNotify(msg,30000);
    }
}

QString dtkComposerNodeDirectory::type(void)
{
    return "fileDir";
}

QString dtkComposerNodeDirectory::titleHint(void)
{
    return "Directory";
}

QString dtkComposerNodeDirectory::inputLabelHint(int port)
{
    if(port == 0)
        return "dir";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeDirectory::outputLabelHint(int port)
{
    if(port == 0)
        return "dir";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeDirectory::value(void)
{
    return d->directory;
}

void dtkComposerNodeDirectory::setValue(QString value)
{
    d->directory = value;
}
