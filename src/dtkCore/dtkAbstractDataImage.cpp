/* dtkAbstractDataImage.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb  2 09:08:09 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Oct  8 09:19:47 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 52
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractDataImage.h>

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkAbstractDataImagePrivate
// /////////////////////////////////////////////////////////////////

class dtkAbstractDataImagePrivate
{
public:
};

// /////////////////////////////////////////////////////////////////
// dtkAbstractDataImage
// /////////////////////////////////////////////////////////////////

dtkAbstractDataImage::dtkAbstractDataImage(void) : dtkAbstractData(), d(new dtkAbstractDataImagePrivate)
{

}

dtkAbstractDataImage::dtkAbstractDataImage(const dtkAbstractDataImage& other): dtkAbstractData(other), d(new dtkAbstractDataImagePrivate)
{

}

dtkAbstractDataImage::~dtkAbstractDataImage(void)
{
    delete d;

    d = NULL;
}

void *dtkAbstractDataImage::image(void)
{
    return this->data();
}

QImage& dtkAbstractDataImage::thumbnail(int width, int height) const
{
    QImage *image = new QImage(width, height, QImage::Format_RGB32);

    QPainter painter(image);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::gray);
    painter.fillRect(image->rect(), Qt::black);

    return *image;
}
