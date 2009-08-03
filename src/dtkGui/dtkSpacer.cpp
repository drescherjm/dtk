/* dtkSpacer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Oct  7 09:25:06 2008 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 14 22:31:29 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkGui/dtkSpacer.h>

dtkSpacer::dtkSpacer(QWidget *parent, int width, int height) : QWidget(parent)
{
    this->setMinimumSize(width, height);

    if(width)
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    else
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

dtkSpacer::~dtkSpacer(void)
{

}

QSize dtkSpacer::sizeHint(void) const 
{
    QSize size = QWidget::sizeHint();
    if (size.width()  < 1) size.setWidth(1);
    if (size.height() < 1) size.setHeight(1);
    return(size);
}
