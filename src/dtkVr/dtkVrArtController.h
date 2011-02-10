/* dtkVrArtController.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb  4 18:09:31 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  4 18:12:01 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRARTCONTROLLER_H
#define DTKVRARTCONTROLLER_H

#include "dtkVrExport.h"

#include <QtCore/QObject>

class dtkVrArtControllerPrivate;

class DTKVR_EXPORT dtkVrArtController : public QObject
{
    Q_OBJECT

public:
     dtkVrArtController(void);
    ~dtkVrArtController(void);

    void setServer(const QString& server);

public slots:
    void start(void);
    void stop(void);

private:
    dtkVrArtControllerPrivate *d;
};

#endif
