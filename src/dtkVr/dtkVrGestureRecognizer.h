/* dtkVrGestureRecognizer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Oct 21 19:11:52 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Oct 26 10:41:26 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
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
     dtkVrGestureRecognizer(void);
    ~dtkVrGestureRecognizer(void);

    void setReceiver(QObject *receiver);

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
