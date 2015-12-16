#pragma once

#include <dtkCore>

#include <${ABSTRACTION}.h>


class ${PLUGIN_CLASS_NAME} : public ${ABSTRACTION}
{
    Q_OBJECT

public:
     ${PLUGIN_CLASS_NAME}(void);
    ~${PLUGIN_CLASS_NAME}(void);

public:
    void run();

};


inline ${ABSTRACTION} *${PLUGIN_CLASS_NAME}Creator(void)
{
    return new ${PLUGIN_CLASS_NAME}();
}
