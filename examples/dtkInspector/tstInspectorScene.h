/* tstInspectorScene.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar 14 15:12:19 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 14 15:25:36 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef TSTINSPECTORSCENE_H
#define TSTINSPECTORSCENE_H

#include <QtGui/QFrame>

class tstInspectorScenePrivate;

class tstInspectorScene : public QFrame
{
    Q_OBJECT

public:
     tstInspectorScene(QWidget *parent = 0);
    ~tstInspectorScene(void);

private:
    tstInspectorScenePrivate *d;
};

#endif
