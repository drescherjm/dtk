// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:

#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerNode.h"

class dtkComposerNodeFactoryPrivate;
class dtkComposerNodeMetaData;

class DTKCOMPOSER_EXPORT dtkComposerNodeFactory : public dtkCorePluginFactory<dtkComposerNode>
{
    Q_OBJECT

public:
             dtkComposerNodeFactory(void);
    virtual ~dtkComposerNodeFactory(void);

public slots:
    dtkComposerNode *create(const QString& node);

public:
    void record(const QString& metadata_file_path, creator func);

public:
    const QStringList& nodes(void) const;
    const QHash<QString, dtkComposerNodeMetaData *>& metaDatas(void) const;

protected:
    dtkComposerNodeFactoryPrivate *d;
};

// ///////////////////////////////////////////////////////////////////
// Helper function for node creation
// ///////////////////////////////////////////////////////////////////

template <typename T> dtkComposerNode *dtkComposerNodeCreator(void) 
{ 
    return new T; 
};

// 
// dtkComposerNodeFactory.h ends here
