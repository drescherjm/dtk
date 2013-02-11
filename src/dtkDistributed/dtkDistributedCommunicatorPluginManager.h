/* dtkDistributedCommunicatorPluginManager.h --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb  4 12:50:38 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb 11 15:24:49 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 23
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkCore/dtkCorePluginManager>
#include <dtkCore/dtkCorePluginManager_p>

class dtkDistributedCommunicatorPluginManager : public dtkCorePluginManager
{
    Q_OBJECT

public:

#pragma mark -
#pragma Manager Management

    void initialize(void);

#pragma mark -
#pragma Plugin Management

    void load(const QString& path);
};
