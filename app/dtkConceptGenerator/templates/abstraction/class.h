#pragma once

#include <dtkCore>

${QOBJECT_INCLUDE}
${QRUNNABLE_INCLUDE}
${CUSTOM_ANCESTOR_INCLUDE}

// ///////////////////////////////////////////////////////////////////
// ${ABSTRACTION} process interface
// ///////////////////////////////////////////////////////////////////

class ${_LAYER_NAME}_EXPORT ${ABSTRACTION} : ${QOBJECT} ${QRUNNABLE} ${CUSTOM_ANCESTOR}
{
    ${Q_OBJECT_MACRO}

public:
             ${ABSTRACTION}(${QOBJECT_CTR_PARAM}) : ${QOBJECT_CTR} ${QRUNNABLE_CTR} ${CUSTOM_ANCESTOR_CTR}{}
    virtual ~${ABSTRACTION}(void) {}
    
public:
//insert inputs here

public:
//insert outputs here

};

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////
DTK_DECLARE_OBJECT        (${ABSTRACTION}*)
${PLUGIN_SYSTEM}

