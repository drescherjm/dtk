/* dtkSpacer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Oct  7 09:25:06 2008 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Mar 23 13:31:15 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 26
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
    this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->setMinimumSize(width, height);

    if(width && !height)
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    else if(!width && height)
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    else
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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
