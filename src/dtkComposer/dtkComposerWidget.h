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

#include "dtkComposerExport.h"
#include "dtkComposerWriter.h"

#include <QtCore>
#include <QtWidgets>

class dtkComposerEvaluator;
class dtkComposerNodeFactory;
class dtkComposerGraph;
class dtkComposerScene;
class dtkComposerSceneNodeComposite;
class dtkComposerStack;
class dtkComposerView;
class dtkComposerCompass;
class dtkComposerPath;
class dtkComposerWriter;
class dtkComposerReader;
class dtkComposerWidgetPrivate;

class DTKCOMPOSER_EXPORT dtkComposerWidget : public QWidget
{
    Q_OBJECT

public:
    dtkComposerWidget(QWidget *parent = 0);
    virtual ~dtkComposerWidget(void);

public:
    void setFactory(dtkComposerNodeFactory *factory);
    void setWriter(dtkComposerWriter *writer);
    void setReader(dtkComposerReader *reader);

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
    void evaluationStopped(void);

public:
    dtkComposerEvaluator *evaluator(void);
    dtkComposerCompass *compass(void);
    dtkComposerNodeFactory *factory(void);
    dtkComposerGraph *graph(void);
    dtkComposerScene *scene(void);
    dtkComposerStack *stack(void);
    dtkComposerView *view(void);
    dtkComposerPath *path(void);
    dtkComposerWriter *writer(void);
    dtkComposerReader *reader(void);

public:
    void updateRemotes(dtkComposerSceneNodeComposite *composite);

private:
    dtkComposerWidgetPrivate *d;
};

//
// dtkComposerWidget.h ends here
