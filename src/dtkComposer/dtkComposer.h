/* dtkComposer.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:34:34 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr 18 17:09:01 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 55
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
class dtkComposerStack;
class dtkComposerView;

class DTKCOMPOSER_EXPORT dtkComposer : public QWidget
{
    Q_OBJECT

public:
             dtkComposer(QWidget *parent = 0);
    virtual ~dtkComposer(void);

public slots:
    virtual bool   open(const QUrl& url);
    virtual bool   open(QString file);
    virtual bool   save(QString file = QString(), dtkComposerWriter::Type type = dtkComposerWriter::Ascii);
    virtual bool insert(QString file);

public slots:
    void run(void);
    void step(void);
    void cont(void);
    void next(void);
    void stop(void);

signals:
    void modified(bool);

public:
    dtkComposerEvaluator *evaluator(void);
    dtkComposerFactory *factory(void);
    dtkComposerGraph *graph(void);
    dtkComposerMachine *machine(void);
    dtkComposerScene *scene(void);
    dtkComposerStack *stack(void);
    dtkComposerView *view(void);

private:
    dtkComposerPrivate *d;
};

#endif
