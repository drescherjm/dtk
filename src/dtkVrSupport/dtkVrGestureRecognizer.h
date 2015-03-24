/* dtkVrGestureRecognizer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Oct 21 19:11:52 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Nov  5 21:24:49 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 15
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkVrSupportExport.h"

#include <QtCore>

class dtkAbstractView;
class dtkVrGestureRecognizerPrivate;

class DTKVRSUPPORT_EXPORT dtkVrGestureRecognizer : public QObject
{
    Q_OBJECT

public:
     dtkVrGestureRecognizer(void);
    ~dtkVrGestureRecognizer(void);

    void setReceiver(QObject *receiver);
    void setView(dtkAbstractView *view);

public slots:
    void startConnection(const QUrl& server);
    void stopConnection(void);

    void postPanEvent(Qt::GestureState state);
    void postSwipeEvent(Qt::GestureState state);
    void postPinchEvent(Qt::GestureState state);
    void postCustomEvent(Qt::GestureState state);
    void postClearEvent(Qt::GestureState state);

private:
    dtkVrGestureRecognizerPrivate *d;
};
