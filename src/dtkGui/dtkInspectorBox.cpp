/* dtkInspectorBox.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jan 31 12:20:34 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 14 15:05:46 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkInspectorBox.h"

#include <dtkCore/dtkGlobal.h>

class dtkInspectorBoxPrivate
{
public:
};

dtkInspectorBox::dtkInspectorBox(QWidget *parent) : QFrame(parent), d(new dtkInspectorBoxPrivate)
{
    this->setStyleSheet(dtkReadFile(":dtkGui/dtkInspectorBox.qss"));
}

dtkInspectorBox::~dtkInspectorBox(void)
{
    delete d;

    d = NULL;
}
