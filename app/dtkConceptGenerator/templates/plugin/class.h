#pragma once

#include <dtkCore>
#include <medCore.h>

#include <${ABSTRACTION}.h>


class ${CLASS_NAME} : public ${ABSTRACTION}
{
    Q_OBJECT

public:
     ${CLASS_NAME}(void);
    ~${CLASS_NAME}(void);

public:
    void run();

};


inline ${ABSTRACTION} *${CLASS_NAME}Creator(void)
{
    return new ${CLASS_NAME}();
}
