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

#include "dtkComposerNodeFactory.h"
#include "dtkComposerNodeMetaData.h"

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

class dtkComposerNodeFactoryPrivate
{
public:
    QStringList nodes;
    QHash<QString, dtkComposerNodeMetaData *> meta_datas;
};

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

dtkComposerNodeFactory::dtkComposerNodeFactory(void) : dtkCorePluginFactory<dtkComposerNode>(), d(new dtkComposerNodeFactoryPrivate)
{

}

dtkComposerNodeFactory::~dtkComposerNodeFactory(void)
{
    QHash<QString, dtkComposerNodeMetaData*>::iterator it = d->meta_datas.begin();
    QHash<QString, dtkComposerNodeMetaData*>::iterator end = d->meta_datas.end();

    for(; it != end; ++it)
        delete *it;

    d->meta_datas.clear();
}

dtkComposerNode *dtkComposerNodeFactory::create(const QString& node)
{
    dtkComposerNode *n = dtkCorePluginFactory<dtkComposerNode>::create(node);
    if (n)
        n->setNodeMetaData(d->meta_datas[node]);

    return n;
}

void dtkComposerNodeFactory::record(const QString& metadata_file_path, creator func)
{
    dtkComposerNodeMetaData *meta_data = new dtkComposerNodeMetaData;

    if (meta_data->setFromFile(metadata_file_path)) {
        d->meta_datas.insert(meta_data->type(), meta_data);
        dtkCorePluginFactory<dtkComposerNode>::record(meta_data->type(), func);
        d->nodes << meta_data->type();

    } else {
        delete meta_data;
    }
}

const QStringList& dtkComposerNodeFactory::nodes(void) const
{
    return d->nodes;
}

const QHash<QString, dtkComposerNodeMetaData *>& dtkComposerNodeFactory::metaDatas(void) const
{
    return d->meta_datas;
}

// 
// dtkComposerNodeFactory.cpp ends here
