/* dtkComposer.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:34:34 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov 19 11:56:27 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 73
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSER_H
#define DTKCOMPOSER_H

#include "dtkComposerExport.h"
#include "dtkComposerWriter.h"

#include <QtCore>
#include <QtGui>

class dtkComposerEvaluator;
class dtkComposerFactory;
class dtkComposerGraph;
class dtkComposerMachine;
class dtkComposerPrivate;
class dtkComposerScene;
class dtkComposerSceneNodeComposite;
class dtkComposerStack;
class dtkComposerView;
class dtkComposerCompass;
class dtkComposerPath;

class DTKCOMPOSER_EXPORT dtkComposer : public QWidget
{
    Q_OBJECT

public:
             dtkComposer(QWidget *parent = 0);
    virtual ~dtkComposer(void);

public:
    void setFactory(dtkComposerFactory *factory);

public slots:
    virtual bool   open(const QUrl& url);
    virtual bool   open(QString file);
    virtual bool   save(QString file = QString(), dtkComposerWriter::Type type = dtkComposerWriter::Ascii);
    virtual bool   saveNode(dtkComposerSceneNodeComposite *node, QString file = QString(), dtkComposerWriter::Type type = dtkComposerWriter::Ascii);
    virtual bool insert(QString file);

public slots:
    void run(void);
    void step(void);
    void cont(void);
    void next(void);
    void stop(void);
    void reset(void);

signals:
    void modified(bool);

public:
    dtkComposerEvaluator *evaluator(void);
    dtkComposerCompass *compass(void);
    dtkComposerFactory *factory(void);
    dtkComposerMachine *machine(void);
    dtkComposerGraph *graph(void);
    dtkComposerScene *scene(void);
    dtkComposerStack *stack(void);
    dtkComposerView *view(void);
    dtkComposerPath *path(void);

public:
    void updateRemotes(dtkComposerSceneNodeComposite * composite);

private:
    dtkComposerPrivate *d;
};

#endif
