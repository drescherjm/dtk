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

#include "dtkComposerExport.h"

#include <QtWidgets>

class dtkComposerViewLayoutItem;
class dtkComposerViewLayoutPrivate;
class dtkComposerViewWidget;

class DTKCOMPOSER_EXPORT dtkComposerViewLayout : public QFrame
{
    Q_OBJECT

public:
    dtkComposerViewLayout(QWidget *parent = 0);
    ~dtkComposerViewLayout(void);

public:
    dtkComposerViewLayoutItem *root(void);
    dtkComposerViewLayoutItem *current(void);

public:
    void setCurrent(dtkComposerViewLayoutItem *item);

signals:
    void focused(dtkComposerViewWidget *view);
    void unfocused(dtkComposerViewWidget *view);

public slots:
    void clear(void);

private:
    dtkComposerViewLayoutPrivate *d;
};

//
// dtkComposerViewLayout.h ends here
