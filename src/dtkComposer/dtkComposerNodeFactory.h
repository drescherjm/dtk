/* dtkComposerNodeFactory.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Wed Apr 10 11:14:39 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 10 15:08:36 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 49
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerNode.h"

class DTKCOMPOSER_EXPORT dtkComposerNodeFactory : public dtkCorePluginFactory<dtkComposerNode>
{
public:
             dtkComposerNodeFactory(void);
    virtual ~dtkComposerNodeFactory(void);

public:
    virtual QStringList implementations(void);

public:
    void initNodeBoolean(void);
    void initNodeControl(void);
    void initNodeNumber (void);
    void initNodeString (void);
};

// ///////////////////////////////////////////////////////////////////
// Helper function for node creation
// ///////////////////////////////////////////////////////////////////

template <typename T> dtkComposerNode *dtkComposerNodeCreator(void) 
{ 
    return new T; 
};
