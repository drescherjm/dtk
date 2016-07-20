#pragma once

#include <dtkCore>
#include <${ABSTRACTION}.h>

class ${PLUGIN_CLASS_NAME}Plugin: public ${ABSTRACTION}Plugin
{
    Q_OBJECT
    Q_INTERFACES(${ABSTRACTION}Plugin)
    Q_PLUGIN_METADATA(IID "fr.inria.${PLUGIN_CLASS_NAME}Plugin" FILE "${PLUGIN_CLASS_NAME}Plugin.json")

public:
     ${PLUGIN_CLASS_NAME}Plugin(void) {}
    ~${PLUGIN_CLASS_NAME}Plugin(void) {}

public:
    void initialize(void);
    void uninitialize(void);
};

