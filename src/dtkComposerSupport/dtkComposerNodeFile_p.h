/* dtkComposerNodeFile_p.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEFILE_P_H
#define DTKCOMPOSERNODEFILE_P_H

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

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
    dtkComposerTransmitterVariant receiver_filters;

public:
    dtkComposerTransmitterEmitterVector<QString> emitter_files;

public:
    dtkContainerVector<QString> files;
};

class dtkComposerNodeFileReadPrivate
{
public:
    dtkComposerTransmitterReceiver<QString> receiver_file;

public:
    dtkComposerTransmitterEmitter<QByteArray> emitter;

public:
    QByteArray data;
};

class dtkComposerNodeFileWritePrivate
{
public:
    dtkComposerTransmitterReceiver<QByteArray> receiver_data;
    dtkComposerTransmitterReceiver<QString> receiver_file;

public:
    dtkComposerTransmitterEmitter<bool> emitter;
    dtkComposerTransmitterEmitter<QString> emitter_file;

public:
    bool success;
    QString filename;
};

#endif
