/* dtkComposerQuickStack.h ---
 * 
 * Author: Julien Wintz
 * Created: Fri Apr 19 11:02:07 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr 19 11:24:19 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkComposer>

#include <QtQuick>

class dtkComposerQuickStackPrivate;

class dtkComposerQuickStack : public QObject
{
    Q_OBJECT

public:
     dtkComposerQuickStack(QObject *parent = 0);
    ~dtkComposerQuickStack(void);

public:
    dtkComposerStack *stack(void);

private:
    dtkComposerQuickStackPrivate *d;
};

QML_DECLARE_TYPE(dtkComposerQuickStack)
