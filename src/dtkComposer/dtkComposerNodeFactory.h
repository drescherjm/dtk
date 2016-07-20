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

#include <dtkCore/dtkCorePluginFactory.h>

class dtkComposerNodeFactoryPrivate;
class dtkComposerNodeMetaData;
class dtkComposerExtension;

// ///////////////////////////////////////////////////////////////////
// dtkComposerNodeFactory definition
// ///////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeFactory : public dtkCorePluginFactory<dtkComposerNode>
{
    Q_OBJECT

public:
    dtkComposerNodeFactory(void);
    virtual ~dtkComposerNodeFactory(void);

public slots:
    dtkComposerNode *create(const QString& node) const;

public:
    void record(const QString& metadata_file_path, creator func);

public:
    void extend(dtkComposerExtension *extension);

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

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////


//
// dtkComposerNodeFactory.h ends here
