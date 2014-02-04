/* dtkComposer.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:34:49 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:03:19 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 449
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkConfig.h>

#include "dtkComposer.h"
#include "dtkComposer_p.h"
#include "dtkComposerCompass.h"
#include "dtkComposerEvaluator.h"
#include "dtkComposerFactory.h"
#include "dtkComposerGraph.h"
#include "dtkComposerMachine.h"
#include "dtkComposerNodeRemote.h"
#include "dtkComposerPath.h"
#include "dtkComposerScene.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerStack.h"
#include "dtkComposerView.h"
#include "dtkComposerWriter.h"
#include "dtkComposerReader.h"

#include <dtkCoreSupport/dtkGlobal.h>
#include <dtkLog/dtkLogger.h>

#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include <QtConcurrent>

// /////////////////////////////////////////////////////////////////
// dtkComposerPrivate
// /////////////////////////////////////////////////////////////////

void dtkComposerPrivate::download(const QUrl& url)
{
    this->file.setAutoRemove(false);

    if (!this->file.open()) {
        qDebug() << DTK_PRETTY_FUNCTION << "Unable to file for saving";
        return;
    }

    this->dwnl_ok = 0;

    QNetworkAccessManager http;

    connect(&http, SIGNAL(requestFinished(QNetworkReply *)), this, SLOT(onRequestFinished(QNetworkReply *)));

    http.get(QNetworkRequest(url));

    while(!this->dwnl_ok)
        qApp->processEvents();

    this->file.close();

    QFileInfo info(this->file);

    this->tempName = info.absoluteFilePath();
}

void dtkComposerPrivate::onRequestFinished(QNetworkReply *reply)
{
    this->file.write(reply->readAll());
    this->file.flush();
    this->dwnl_ok = 1;
}

// /////////////////////////////////////////////////////////////////
// dtkComposer
// /////////////////////////////////////////////////////////////////

dtkComposer::dtkComposer(QWidget *parent) : QWidget(parent), d(new dtkComposerPrivate)
{
    d->machine = new dtkComposerMachine;
    d->factory = new dtkComposerFactory;
    d->graph = new dtkComposerGraph;
    d->stack = new dtkComposerStack;
    d->scene = new dtkComposerScene;
    d->evaluator = new dtkComposerEvaluator;
    d->writer = new dtkComposerWriter;
    d->reader = new dtkComposerReader;

    d->scene->setFactory(d->factory);
    d->scene->setMachine(d->machine);
    d->scene->setStack(d->stack);
    d->scene->setGraph(d->graph);

    d->view = new dtkComposerView(this);
    d->view->setScene(d->scene);

    d->path = new dtkComposerPath(this);
    d->path->setScene(d->scene);
    
    d->compass = new dtkComposerCompass;
    d->compass->setScene(d->scene);
    d->compass->setView(d->view);

    d->evaluator->setGraph(d->graph);

    d->writer->setScene(d->scene);

    d->reader->setFactory(d->factory);
    d->reader->setScene(d->scene);
    d->reader->setGraph(d->graph);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->path);
    layout->addWidget(d->view);

    connect(d->scene, SIGNAL(modified(bool)), this, SIGNAL(modified(bool)));
    connect(d->evaluator, SIGNAL(evaluationStopped()), this, SIGNAL(evaluationStopped()));
}

dtkComposer::~dtkComposer(void)
{
    delete d->machine;
    delete d->factory;
    delete d->graph;
    delete d->stack;
    delete d->evaluator;
    delete d->writer;
    delete d->reader;
    delete d;
    
    d = NULL;
}

void dtkComposer::setFactory(dtkComposerFactory *factory)
{
    delete d->factory;

    d->factory = factory;

    d->scene->setFactory(d->factory);
    d->reader->setFactory(d->factory);
}

void dtkComposer::setWriter(dtkComposerWriter *writer)
{
  if(writer) {
    delete d->writer;

    d->writer = writer;
    d->writer->setScene(d->scene);
  }
}

void dtkComposer::setReader(dtkComposerReader *reader)
{
  if(reader) {
    delete d->reader;

    d->reader = reader;
    d->reader->setFactory(d->factory);
    d->reader->setScene(d->scene);
    d->reader->setGraph(d->graph);
  }
}

bool dtkComposer::open(const QUrl& url)
{
    d->download(url);

    bool status = false;

    if(!d->tempName.isEmpty())
        status = this->open(d->tempName);

    return status;
}

bool dtkComposer::open(QString file)
{
    if (!file.isEmpty()) {

        d->reader->read(file);

        d->fileName = file;
    }

    return true;
}

bool dtkComposer::save(QString file, dtkComposerWriter::Type type)
{
    return saveNode(d->scene->root(), file, type);
}

bool dtkComposer::saveNode(dtkComposerSceneNodeComposite *node, QString file, dtkComposerWriter::Type type)
{
    QString fName = d->fileName;

    if(!file.isEmpty())
        fName = file;

    d->writer->writeNode(node, fName, type);

    const QFileInfo fi(fName);
    d->fileName = fi.absoluteFilePath();

    return true;
}

bool dtkComposer::insert(QString file)
{
    if (!file.isEmpty()) {

        d->reader->read(file, true);
    }

    return true;
}

void dtkComposer::updateRemotes(dtkComposerSceneNodeComposite *composite)
{
#if defined(DTK_BUILD_DISTRIBUTED)
    foreach(dtkComposerSceneNode *node, composite->nodes()) {
        if (dtkComposerNodeRemote *remote = dynamic_cast<dtkComposerNodeRemote *>(node->wrapee()))
            remote->setComposition(d->writer->toXML(dynamic_cast<dtkComposerSceneNodeComposite *>(node)));
        else if (dtkComposerSceneNodeComposite *sub = dynamic_cast<dtkComposerSceneNodeComposite *>(node))
            this->updateRemotes(sub);
        else if (dtkComposerSceneNodeControl *ctrl = dynamic_cast<dtkComposerSceneNodeControl *>(node))
            foreach(dtkComposerSceneNodeComposite *block, ctrl->blocks())
                this->updateRemotes(block);
    }
#else
    Q_UNUSED(composite);
#endif
}


void dtkComposer::run(void)
{
    this->updateRemotes(d->scene->root());

    QtConcurrent::run(d->evaluator, &dtkComposerEvaluator::run, false);

    d->graph->update();
}

void dtkComposer::step(void)
{
    d->evaluator->step();
    d->evaluator->logStack();

    d->graph->update();
}

void dtkComposer::cont(void)
{
    this->updateRemotes(d->scene->root());

    QtConcurrent::run(d->evaluator, &dtkComposerEvaluator::cont, false);

    d->graph->update();
}

void dtkComposer::next(void)
{
    QtConcurrent::run(d->evaluator, &dtkComposerEvaluator::next, false);

    d->graph->update();
}

void dtkComposer::stop(void)
{
    d->evaluator->stop();
}

void dtkComposer::reset(void)
{
    dtkTrace() << "Resetting composition ";

    d->writer->setScene(d->scene);
    QString data = d->writer->toXML(d->scene->root(), false).toString();

    d->reader->readString(data);

    d->evaluator->reset();

}

dtkComposerEvaluator *dtkComposer::evaluator(void)
{
    return d->evaluator;
}

dtkComposerMachine *dtkComposer::machine(void)
{
    return d->machine;
}

dtkComposerFactory *dtkComposer::factory(void)
{
    return d->factory;
}

dtkComposerGraph *dtkComposer::graph(void)
{
    return d->graph;
}

dtkComposerScene *dtkComposer::scene(void)
{
    return d->scene;
}

dtkComposerStack *dtkComposer::stack(void)
{
    return d->stack;
}

dtkComposerView *dtkComposer::view(void)
{
    return d->view;
}

dtkComposerPath *dtkComposer::path(void)
{
    return d->path;
}

dtkComposerCompass *dtkComposer::compass(void)
{
    return d->compass;
}

dtkComposerWriter *dtkComposer::writer(void)
{
    return d->writer;
}
