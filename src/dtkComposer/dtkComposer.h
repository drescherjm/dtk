/* dtkComposer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Sep  4 10:12:32 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Oct 18 13:25:35 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 94
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

#include <QtCore/QUrl>

#include <QtGui/QWidget>

class dtkAbstractData;
class dtkAbstractProcess;
class dtkAbstractView;

class dtkComposerNode;
class dtkComposerNodeFactory;
class dtkComposerPrivate;
class dtkComposerScene;
class dtkComposerView;

class DTKCOMPOSER_EXPORT dtkComposer : public QWidget
{
    Q_OBJECT

public:
             dtkComposer(QWidget *parent = 0);
    virtual ~dtkComposer(void);

    void setBackgroundColor(const QColor& color);
    void setFactory(dtkComposerNodeFactory *factory);
    void setFileName(const QString& fileName);

    bool isModified(void);

    QString fileName(void);

public slots:
    bool   open(const QUrl& url);
    bool   open(QString fileName);
    bool   save(QString fileName = QString());
    bool insert(QString fileName);

signals:
    void compositionChanged(void);
    void titleChanged(QString title);

signals:
    void dataSelected(dtkAbstractData *data);
    void processSelected(dtkAbstractProcess *process);
    void viewSelected(dtkAbstractView *view);
    
    void nodeAdded(dtkComposerNode *node);
    void nodeRemoved(dtkComposerNode *node);
    void nodeSelected(dtkComposerNode *node);
   
    void selectionCleared(void);

    void pathChanged(dtkComposerNode *);

signals:
    void evaluationStarted(void);
    void evaluationStopped(void);

public slots:
    void   group(QList<dtkComposerNode *> nodes);
    void ungroup(dtkComposerNode *node);

public slots:
   void onDataSelected(dtkAbstractData *data);
   void onProcessSelected(dtkAbstractProcess *process);
   void onViewSelected(dtkAbstractView *view);

public slots:
   void startEvaluation(void);
   void stopEvaluation(void);

public slots:
   void copy(void);
   void paste(void);

protected:
   dtkComposerScene *scene(void);
   dtkComposerView *view(void);

private:
    dtkComposerPrivate *d;
};

#endif
