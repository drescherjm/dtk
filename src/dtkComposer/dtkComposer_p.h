/* dtkComposer_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:35:09 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  1 13:40:28 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 53
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSER_P_H
#define DTKCOMPOSER_P_H

#include <QtCore>

class dtkComposerFactory;
class dtkComposerMachine;
class dtkComposerScene;
class dtkComposerStack;
class dtkComposerView;

class dtkComposerPrivate : public QObject
{
    Q_OBJECT

public:
    void download(const QUrl& url);

public slots:
    void onRequestFinished(int id, bool error);

public:
    dtkComposerFactory *factory;
    dtkComposerMachine *machine;
    dtkComposerScene *scene;
    dtkComposerStack *stack;
    dtkComposerView *view;

public:
    QString fileName;
    QString tempName;

    int dwnl_id;
    int dwnl_ok;
};

#endif
