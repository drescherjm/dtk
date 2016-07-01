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

#include <QtCore>

class dtkComposerNodeFactory;
class dtkComposerExtensionPlugin;
class dtkComposerExtensionPluginManager;
class dtkComposerExtensionPluginFactory;

namespace dtkComposer
{
    namespace node {
        DTKCOMPOSER_EXPORT dtkComposerNodeFactory& factory(void);
        DTKCOMPOSER_EXPORT void initialize(void);
    }
    namespace extension {
        DTKCOMPOSER_EXPORT dtkComposerExtensionPluginFactory& pluginFactory(void);
        DTKCOMPOSER_EXPORT dtkComposerExtensionPluginManager& pluginManager(void);
        DTKCOMPOSER_EXPORT void initialize(const QString& path = "");
    }
}

//
// dtkComposer.h ends here
