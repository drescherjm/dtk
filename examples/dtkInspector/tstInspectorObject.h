/* tstInspectorObject.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar 14 15:37:16 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 14 15:37:36 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef TSTINSPECTOROBJECT_H
#define TSTINSPECTOROBJECT_H

#include <QtGui/QFrame>

class tstInspectorObjectPrivate;

class tstInspectorObject : public QFrame
{
    Q_OBJECT

public:
     tstInspectorObject(QWidget *parent = 0);
    ~tstInspectorObject(void);

private:
    tstInspectorObjectPrivate *d;
};

#endif
