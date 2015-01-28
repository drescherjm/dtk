/* dtkComposerNodeFile_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Sep 21 16:12:57 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr  5 09:17:48 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMeta>
#include <QtCore>

class dtkComposerNodeFilePrivate : public QObject
{
    Q_OBJECT

public:
    void download(const QUrl& url);

public slots:
    void onRequestFinished(int id, bool error);

public:
    QString fileName;
    QString tempName;

    int dwnl_id;
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
