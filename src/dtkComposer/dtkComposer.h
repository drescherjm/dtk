/* dtkComposer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Sep  4 10:12:32 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jul 27 11:46:34 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 36
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

#include <QtGui/QWidget>

class dtkAbstractData;
class dtkAbstractProcess;
class dtkAbstractView;
class dtkComposerNode;
class dtkComposerNodeFactory;
class dtkComposerPrivate;

class DTKCOMPOSER_EXPORT dtkComposer : public QWidget
{
    Q_OBJECT

public:
             dtkComposer(QWidget *parent = 0);
    virtual ~dtkComposer(void);
    
    void setFactory(dtkComposerNodeFactory *factory);

signals:
    void dataSelected(dtkAbstractData *data);
    void processSelected(dtkAbstractProcess *process);
    void viewSelected(dtkAbstractView *view);
    
    void nodeAdded(dtkComposerNode *node);
    void nodeRemoved(dtkComposerNode *node);
   
signals:
    void evaluationStarted(void);
    void evaluationStopped(void);

public slots:
   void onDataSelected(dtkAbstractData *data);
   void onProcessSelected(dtkAbstractProcess *process);
   void onViewSelected(dtkAbstractView *view);

public slots:
   void startEvaluation(void);
   void stopEvaluation(void);

private:
    dtkComposerPrivate *d;
};

#endif
