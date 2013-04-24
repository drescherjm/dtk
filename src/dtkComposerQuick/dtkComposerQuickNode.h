/* dtkComposerQuickNode.h ---
 * 
 * Author: Julien Wintz
 * Created: Fri Apr 19 10:15:52 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr 19 11:12:45 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkComposer>

class dtkComposerQuickNodePrivate;

class dtkComposerQuickNode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type WRITE setType)

public:
     dtkComposerQuickNode(QObject *parent = 0);
    ~dtkComposerQuickNode(void);

#pragma mark -
#pragma mark Internals
    
    dtkComposerNode *node(void);
    void setNode(dtkComposerNode *node);

#pragma mark -
#pragma mark Properties - getters
    
    const QString& type(void);

#pragma mark -
#pragma mark Properties - setters
    
    void setType(const QString& type);


private:
    dtkComposerQuickNodePrivate *d;
};
