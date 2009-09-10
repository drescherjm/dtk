/* dtkInspectorScene.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Sep  9 19:06:15 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep 10 17:01:44 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKINSPECTORSCENE_H
#define DTKINSPECTORSCENE_H

#include <QtGui>

class dtkAbstractData;
class dtkAbstractProcess;
class dtkAbstractView;
class dtkInspectorScenePrivate;

class dtkInspectorScene : public QWidget
{
    Q_OBJECT

public:
     dtkInspectorScene(QWidget *parent = 0);
    ~dtkInspectorScene(void);

signals:
    void dataSelected(dtkAbstractData *data);
    void processSelected(dtkAbstractProcess *process);
    void viewSelected(dtkAbstractView *view);

public slots:
    void addData(dtkAbstractData *data, QString type);
    void addProcess(dtkAbstractProcess *process, QString type);
    void addView(dtkAbstractView *view, QString type);

public slots:
   void onDataSelected(dtkAbstractData *data);
   void onProcessSelected(dtkAbstractProcess *process);
   void onViewSelected(dtkAbstractView *view);

private slots:
    void onItemClicked(QTreeWidgetItem *item, int column);

private:
    dtkInspectorScenePrivate *d;
};

#endif
