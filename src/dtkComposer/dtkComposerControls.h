/* dtkComposerControls.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Nov 20 16:16:42 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:33:24 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 30
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once


#include "dtkComposerExport.h"

#include <QtGui>
#include <QtWidgets>

class dtkComposerControlsPrivate;
class dtkComposerScene;

class DTKCOMPOSER_EXPORT  dtkComposerControls : public QFrame
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

