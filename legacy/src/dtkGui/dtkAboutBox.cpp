/* dtkAboutBox.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Apr 19 12:52:49 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 19 13:12:04 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkAboutBox.h"

class dtkAboutBoxPrivate
{
public:
};

dtkAboutBox::dtkAboutBox(QWidget *parent) : QMessageBox(parent), d(new dtkAboutBoxPrivate)
{
    this->setIconPixmap(QPixmap(":dtkGui/pixmaps/dtk.png").scaledToHeight(150));
}

dtkAboutBox::~dtkAboutBox(void)
{
    delete d;

    d = NULL;
}
