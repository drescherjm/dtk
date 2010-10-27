/* dtkVrHeadRecognizer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Oct 26 12:38:20 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Oct 26 13:23:25 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRHEADRECOGNIZER_H
#define DTKVRHEADRECOGNIZER_H

#include <QtCore>

class dtkAbstractView;
class dtkVrHeadRecognizerPrivate;

class dtkVrHeadRecognizer : public QObject
{
    Q_OBJECT

public:
     dtkVrHeadRecognizer(void);
    ~dtkVrHeadRecognizer(void);

    void setReceiver(dtkAbstractView *receiver);

public slots:
    void startConnection(const QUrl& server);
    void stopConnection(void);

protected slots:
    void onMoved(void);
    void onButtonPressed(int);
    void onButtonReleased(int);

private:
    dtkVrHeadRecognizerPrivate *d;
};

#endif // DTKVRHEADRECOGNIZER_H
