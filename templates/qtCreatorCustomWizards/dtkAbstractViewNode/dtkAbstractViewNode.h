/* %NodeName%.h ---
 *
 * Author: %Author%
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef %NodeName:u%_H
#define %NodeName:u%_H

#include <dtkComposer/dtkComposerNodeLeafView.h>

#include "%Layer%Export.h"

class %NodeName%Private;

// /////////////////////////////////////////////////////////////////
// %NodeName% interface
// /////////////////////////////////////////////////////////////////

class %Layer:u%_EXPORT %NodeName% : public dtkComposerNodeLeafView
{
public:
     %NodeName%(void);
    ~%NodeName%(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

public:
    bool isAbstractView(void) const;

    QString abstractViewType(void) const;
    
public:
    void run(void);

private:
    %NodeName%Private *d;
};

#endif

