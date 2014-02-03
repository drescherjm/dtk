/* %1.h ---
 *
 * Author: %Author%
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef %2_H
#define %2_H

#include <dtkComposer/dtkComposerNodeLeaf%5.h>

#include "%3ComposerExport.h"

class %1Private;

// /////////////////////////////////////////////////////////////////
// %1 interface
// /////////////////////////////////////////////////////////////////

class %4COMPOSER_EXPORT %1 : public dtkComposerNodeLeaf%5
{
public:
     %1(void);
    ~%1(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

public:
    bool isAbstract%5(void) const;

    QString abstract%5Type(void) const;
    
public:
    void run(void);

private:
    %1Private *d;
};

#endif

