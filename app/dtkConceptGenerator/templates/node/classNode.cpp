// Copyright: INRIA

#include <dtkComposer>

#include "${CLASS_NAME}.h"

class ${CLASS_NAME}Private
{
public:

};

${CLASS_NAME}::${CLASS_NAME}(void) : dtkComposerNodeObject<${ABSTRACTION}>(), d(new ${CLASS_NAME}Private())
{
    this->setFactory(${LAYER_NAME}::${NAMESPACE}::pluginFactory());

}

${CLASS_NAME}::~${CLASS_NAME}Node(void)
{
    delete d;
}

void ${CLASS_NAME}::run(void)
{
    
}

