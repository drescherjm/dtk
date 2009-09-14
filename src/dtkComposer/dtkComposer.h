/* dtkComposer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Sep  4 10:12:32 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Sep 11 23:08:59 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSER_H
#define DTKCOMPOSER_H

#include <QtGui/QWidget>

class dtkAbstractData;
class dtkAbstractProcess;
class dtkAbstractView;
class dtkComposerPrivate;

class dtkComposer : public QWidget
{
    Q_OBJECT

public:
     dtkComposer(QWidget *parent = 0);
    ~dtkComposer(void);

    void run(void);
    void stop(void);

signals:
   void dataSelected(dtkAbstractData *data);
   void processSelected(dtkAbstractProcess *process);
   void viewSelected(dtkAbstractView *view);

public slots:
   void onDataSelected(dtkAbstractData *data);
   void onProcessSelected(dtkAbstractProcess *process);
   void onViewSelected(dtkAbstractView *view);

private:
    dtkComposerPrivate *d;
};

#endif
