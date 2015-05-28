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

#include <dtkMeta>

#include <QtCore>
#include <QtNetwork>

class dtkComposerNodeFilePrivate : public QObject
{
    Q_OBJECT

public:
    void download(const QUrl& url);

public slots:
    void onRequestFinished(QNetworkReply *reply);

public:
    QString fileName;
    QString tempName;

    QTemporaryFile file;
    int dwnl_ok;

public:
    dtkComposerTransmitterReceiver<QString> receiver;

public:
    dtkComposerTransmitterEmitter<QString> emitter;
};


class dtkComposerNodeFileExistsPrivate
{
public:
    bool exists;

public:
    dtkComposerTransmitterReceiver<QString> receiver;

public:
    dtkComposerTransmitterEmitter<bool> emitter;
};


class dtkComposerNodeFileListPrivate
{
public:
    bool exists;

public:
    dtkComposerTransmitterReceiver<QString> receiver_dir;
    dtkComposerTransmitterReceiverVariant receiver_filters;

public:
    dtkComposerTransmitterEmitter< QStringList *> emitter_files;

public:
   QStringList files;
};

class dtkComposerNodeFileReadPrivate
{
public:
    dtkComposerTransmitterReceiver<QString> receiver_file;

public:
    dtkComposerTransmitterEmitter<QByteArray *> emitter;

public:
    QByteArray data;
};

class dtkComposerNodeFileWritePrivate
{
public:
    dtkComposerTransmitterReceiver<QByteArray *> receiver_data;
    dtkComposerTransmitterReceiver<QString> receiver_file;

public:
    dtkComposerTransmitterEmitter<bool> emitter;
    dtkComposerTransmitterEmitter<QString> emitter_file;

public:
    bool success;
    QString filename;
};

class dtkComposerNodeDirectoryPrivate
{
 public:
    dtkComposerTransmitterReceiver<QString> receiver_directory;

 public:
    dtkComposerTransmitterEmitter<QString> emitter_directory;

 public:
    QString directory;
};

//
// dtkComposerNodeFile_p.h ends here
