/* dtkComposerControls.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Nov 20 16:16:42 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 21 14:00:38 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERCONTROLS_H
#define DTKCOMPOSERCONTROLS_H

#include "dtkComposerExport.h"

#include <QtGui>

class dtkComposerControlsPrivate;
class dtkComposerScene;

class DTKCOMPOSER_EXPORT dtkComposerControls : public QFrame
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
