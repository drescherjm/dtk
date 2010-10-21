/* dtkVrGestureRecognizer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Oct 21 19:11:52 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Oct 21 19:11:56 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRGESTURERECOGNIZER_H
#define DTKVRGESTURERECOGNIZER_H

#include <QtCore>

class dtkVrGestureRecognizerPrivate;

class dtkVrGestureRecognizer : public QObject
{
    Q_OBJECT

public:
     dtkVrGestureRecognizer(QObject *receiver);
    ~dtkVrGestureRecognizer(void);

public slots:
    void startConnection(const QUrl& server);
    void stopConnection(void);

    void postPanEvent(void);
    void postSwipeEvent(void);
    void postPinchEvent(void);
    void postClearEvent(void);

private:
    dtkVrGestureRecognizerPrivate *d;
};

#endif // DTKVRGESTURERECOGNIZER_H
