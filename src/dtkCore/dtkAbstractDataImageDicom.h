/* dtkAbstractDataImageDicom.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Jun  2 11:04:59 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jul 31 23:19:54 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 27
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATAIMAGEDICOM_H
#define DTKABSTRACTDATAIMAGEDICOM_H

#include <QtGui/QImage>

#include <dtkCore/dtkAbstractDataImage.h>

class dtkAbstractDataImageDicomPrivate;

class DTKCORE_EXPORT dtkAbstractDataImageDicom : public dtkAbstractDataImage
{
    Q_OBJECT

public:
             dtkAbstractDataImageDicom(void);
             dtkAbstractDataImageDicom(const dtkAbstractDataImageDicom& other);
    virtual ~dtkAbstractDataImageDicom(void);

    virtual QImage thumbnail(void) { return QImage(); }

    virtual QString patient(void) const { return QString(); }
    virtual QString   study(void) const { return QString(); }
    virtual QString  series(void) const { return QString(); }

    virtual double windowCenter(void) const { return 0.0; }
    virtual double windowWidth (void) const { return 0.0; }

    virtual void setWindowCenter(const double center) { Q_UNUSED(center); }
    virtual void setWindowWidth (const double width)  { Q_UNUSED(width);  }

private:
    dtkAbstractDataImageDicomPrivate *d;
};

#endif
