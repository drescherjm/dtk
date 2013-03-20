/* dtkComposerNodeFile_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Sep 21 16:12:57 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep 24 12:12:14 2012 (+0200)
 *           By: tkloczko
 *     Update #: 7
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

#endif
