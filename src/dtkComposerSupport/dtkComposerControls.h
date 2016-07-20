/* dtkComposerControls.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Nov 20 16:16:42 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. juin  4 15:00:10 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 27
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERCONTROLS_H
#define DTKCOMPOSERCONTROLS_H

#include "dtkComposerSupportExport.h"

#include <QtWidgets>

class dtkComposerControlsPrivate;
class dtkComposerScene;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerControls : public QFrame
{
    Q_OBJECT

public:
    dtkComposerControls(QWidget *parent = 0);
    ~dtkComposerControls(void);

public:
    void setScene(dtkComposerScene *scene);

protected slots:
    void setup(void);
    void setup(int index);

private:
    dtkComposerControlsPrivate *d;
};

#endif
