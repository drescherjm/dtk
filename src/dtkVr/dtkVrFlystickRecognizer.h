/* dtkVrFlystickRecognizer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb  7 10:04:10 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  7 10:04:34 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRFLYSTICKRECOGNIZER_H
#define DTKVRFLYSTICKRECOGNIZER_H

#include "dtkVrExport.h"

#include <QtCore>

class dtkAbstractView;
class dtkVrFlystickRecognizerPrivate;

class DTKVR_EXPORT dtkVrFlystickRecognizer : public QObject
{
    Q_OBJECT

public:
     dtkVrFlystickRecognizer(void);
    ~dtkVrFlystickRecognizer(void);

    void setView(dtkAbstractView *view);

public slots:
    void startConnection(const QUrl& server);
    void stopConnection(void);

protected slots:
    void onMoved(void);
    void onButtonPressed(int);
    void onButtonReleased(int);

private:
    dtkVrFlystickRecognizerPrivate *d;
};

#endif // DTKVRFLYSTICKRECOGNIZER_H
