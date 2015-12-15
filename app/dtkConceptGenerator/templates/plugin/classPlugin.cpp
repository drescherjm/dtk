#include "${PLUGIN_CLASS_NAME}.h"
#include "${PLUGIN_CLASS_NAME}Plugin.h"

#include <dtkCore>
#include "${LAYER_NAME}.h"

// ///////////////////////////////////////////////////////////////////
// ${PLUGIN_CLASS_NAME}Plugin
// ///////////////////////////////////////////////////////////////////

void ${PLUGIN_CLASS_NAME}Plugin::initialize(void)
{
    ${LAYER_NAME}::${NAMESPACE}::pluginFactory().record("${PLUGIN_CLASS_NAME}", ${PLUGIN_CLASS_NAME}Creator);
}

void ${PLUGIN_CLASS_NAME}Plugin::uninitialize(void)
{

}

// ///////////////////////////////////////////////////////////////////
// Plugin meta data
// ///////////////////////////////////////////////////////////////////

DTK_DEFINE_PLUGIN(${PLUGIN_CLASS_NAME})

