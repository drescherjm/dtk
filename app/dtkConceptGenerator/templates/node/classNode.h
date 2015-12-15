// Copyright: INRIA

#pragma once

#include <dtkComposer>
#include "${ABSTRACTION}.h"

class ${NODE_CLASS_NAME}Private;

// ///////////////////////////////////////////////////////////////////
// ${NODE_CLASS_NAME}
// ///////////////////////////////////////////////////////////////////

class ${NODE_CLASS_NAME} : public dtkComposerNodeObject<${ABSTRACTION}>
{
public:
     ${NODE_CLASS_NAME}(void);
    ~${NODE_CLASS_NAME}(void);

public:
    void run(void);

private:
    ${NODE_CLASS_NAME}Private *d;
};
