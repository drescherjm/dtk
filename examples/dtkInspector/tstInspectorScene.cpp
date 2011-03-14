/* tstInspectorScene.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar 14 15:26:37 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 14 15:27:52 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstInspectorScene.h"

class tstInspectorScenePrivate
{
public:
    
};

tstInspectorScene::tstInspectorScene(QWidget *parent) : QFrame(parent), d(new tstInspectorScenePrivate)
{

}

tstInspectorScene::~tstInspectorScene(void)
{
    delete d;

    d = NULL;
}
