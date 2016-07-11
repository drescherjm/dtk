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

#include <dtkConfig.h>

#include "dtkComposerWidget.h"
#include "dtkComposerWidget_p.h"
#include "dtkComposerCompass.h"
#include "dtkComposerEvaluator.h"
#include "dtkComposerNodeFactory.h"
#include "dtkComposerGraph.h"
#include "dtkComposerNodeRemote.h"
#include "dtkComposerPath.h"
#include "dtkComposerScene.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerStack.h"
#include "dtkComposerView.h"
#include "dtkComposerWriter.h"
#include "dtkComposerReader.h"
#include "dtkComposer.h"

#include <dtkLog>

#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include <QtConcurrent>

// /////////////////////////////////////////////////////////////////
// dtkComposerWidgetPrivate
// /////////////////////////////////////////////////////////////////

void dtkComposerWidgetPrivate::download(const QUrl& url)
{
    this->file.setAutoRemove(false);

    if (!this->file.open()) {
        qDebug() << Q_FUNC_INFO << "Unable to file for saving";
        return;
    }

    this->dwnl_ok = 0;

    QNetworkAccessManager http;

    connect(&http, SIGNAL(finished(QNetworkReply *)), this, SLOT(onRequestFinished(QNetworkReply *)));

    http.get(QNetworkRequest(url));

    while(!this->dwnl_ok)
        qApp->processEvents();

    this->file.close();

    QFileInfo info(this->file);

    this->tempName = info.absoluteFilePath();
}

void dtkComposerWidgetPrivate::onRequestFinished(QNetworkReply *reply)
{
    this->file.write(reply->readAll());
    this->file.flush();
    this->dwnl_ok = 1;
}

// /////////////////////////////////////////////////////////////////
// dtkComposer
// /////////////////////////////////////////////////////////////////

dtkComposerWidget::dtkComposerWidget(QWidget *parent) : QWidget(parent), d(new dtkComposerWidgetPrivate)
{
    d->factory = &(dtkComposer::node::factory());
    d->graph = new dtkComposerGraph;
    d->stack = new dtkComposerStack;
    d->scene = new dtkComposerScene;
    d->evaluator = new dtkComposerEvaluator;
    d->writer = new dtkComposerWriter;
    d->reader = new dtkComposerReader;

    d->scene->setFactory(d->factory);
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

dtkComposerWidget::~dtkComposerWidget(void)
{
    delete d->graph;
    delete d->stack;
    delete d->evaluator;
    delete d->writer;
    delete d->reader;
    delete d;

    d = NULL;
}

void dtkComposerWidget::setFactory(dtkComposerNodeFactory *factory)
{
    delete d->factory;

    d->factory = factory;

    d->scene->setFactory(d->factory);
    d->reader->setFactory(d->factory);
}

void dtkComposerWidget::setWriter(dtkComposerWriter *writer)
{
    if(writer) {

        delete d->writer;

        d->writer = writer;
        d->writer->setScene(d->scene);
    }
}

void dtkComposerWidget::setReader(dtkComposerReader *reader)
{
    if(reader) {

        delete d->reader;

        d->reader = reader;
        d->reader->setFactory(d->factory);
        d->reader->setScene(d->scene);
        d->reader->setGraph(d->graph);
    }
}

bool dtkComposerWidget::open(const QUrl& url)
{
    d->download(url);

    bool status = false;

    if(!d->tempName.isEmpty())
        status = this->open(d->tempName);

    return status;
}

bool dtkComposerWidget::open(QString file)
{
    if (!file.isEmpty()) {

        d->reader->read(file);

        d->fileName = file;
    }

    return true;
}

bool dtkComposerWidget::save(QString file, dtkComposerWriter::Type type)
{
    return saveNode(d->scene->root(), file, type);
}

bool dtkComposerWidget::saveNode(dtkComposerSceneNodeComposite *node, QString file, dtkComposerWriter::Type type)
{
    QString fName = d->fileName;

    if(!file.isEmpty())
        fName = file;

    d->writer->writeNode(node, fName, type);

    const QFileInfo fi(fName);
    d->fileName = fi.absoluteFilePath();

    return true;
}

bool dtkComposerWidget::insert(QString file)
{
    if (!file.isEmpty()) {

        d->reader->read(file, true);
    }

    return true;
}

void dtkComposerWidget::updateRemotes(dtkComposerSceneNodeComposite *composite)
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


void dtkComposerWidget::run(void)
{
    this->updateRemotes(d->scene->root());

    if (d->scene->checkImplementations()) {
        QtConcurrent::run(d->evaluator, &dtkComposerEvaluator::run, false);
    } else {
        emit evaluationStopped();
    }
}

void dtkComposerWidget::step(void)
{
    d->evaluator->step();
    d->evaluator->logStack();

}

void dtkComposerWidget::cont(void)
{
    this->updateRemotes(d->scene->root());

    QtConcurrent::run(d->evaluator, &dtkComposerEvaluator::cont, false);

}

void dtkComposerWidget::next(void)
{
    QtConcurrent::run(d->evaluator, &dtkComposerEvaluator::next, false);

}

void dtkComposerWidget::stop(void)
{
    d->evaluator->stop();
}

void dtkComposerWidget::reset(void)
{
    dtkTrace() << "Resetting composition ";

    d->writer->setScene(d->scene);
    QString data = d->writer->toXML(d->scene->root(), false).toString();

    d->reader->readString(data);

    d->evaluator->reset();
}

dtkComposerEvaluator *dtkComposerWidget::evaluator(void)
{
    return d->evaluator;
}

dtkComposerNodeFactory *dtkComposerWidget::factory(void)
{
    return d->factory;
}

dtkComposerGraph *dtkComposerWidget::graph(void)
{
    return d->graph;
}

dtkComposerScene *dtkComposerWidget::scene(void)
{
    return d->scene;
}

dtkComposerStack *dtkComposerWidget::stack(void)
{
    return d->stack;
}

dtkComposerView *dtkComposerWidget::view(void)
{
    return d->view;
}

dtkComposerPath *dtkComposerWidget::path(void)
{
    return d->path;
}

dtkComposerCompass *dtkComposerWidget::compass(void)
{
    return d->compass;
}

dtkComposerWriter *dtkComposerWidget::writer(void)
{
    return d->writer;
}

//
// dtkComposerWidget.cpp ends here
