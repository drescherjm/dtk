/* tstInspectorObject.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar 14 15:26:37 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 14 15:37:54 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstInspectorObject.h"

class tstInspectorObjectPrivate
{
public:
    
};

tstInspectorObject::tstInspectorObject(QWidget *parent) : QFrame(parent), d(new tstInspectorObjectPrivate)
{

}

tstInspectorObject::~tstInspectorObject(void)
{
    delete d;

    d = NULL;
}
