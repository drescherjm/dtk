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

class dtkComposerNodeMetaDataPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeMetaData
{
public:
             dtkComposerNodeMetaData(void);
    virtual ~dtkComposerNodeMetaData(void);

public:
    bool setFromFile(const QString& file_path);

public:
    void setTitle(const QString& title);
    void setKind(const QString& kind);
    void setType(const QString& type);
    void setTags(const QStringList& tags);
    void setDescription(const QString& description);
    void appendInputLabel(const QString& label);
    void appendOutputLabel(const QString& label);

public:
    const QString& title(void) const;
    dtkComposerNode::Kind kind(void) const;
    const QString& type(void) const;
    const QStringList& tags(void) const;
    const QString& description(void) const;
    const QStringList& inputLabels(void) const;
    const QStringList& outputLabels(void) const;

public:
    dtkComposerNodeMetaDataPrivate *d;
};

// 
// dtkComposerNodeMetaData.h ends here
