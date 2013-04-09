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

