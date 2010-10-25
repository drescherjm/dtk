/* dtkVrGestureRecognizer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Oct 21 19:11:52 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 25 09:57:20 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
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

    void postPanEvent(Qt::GestureState state);
    void postSwipeEvent(Qt::GestureState state);
    void postPinchEvent(Qt::GestureState state);
    void postClearEvent(Qt::GestureState state);

private:
    dtkVrGestureRecognizerPrivate *d;
};

#endif // DTKVRGESTURERECOGNIZER_H
