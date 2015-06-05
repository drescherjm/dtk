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

#include "dtkWidgetsExport.h"

#include <QtWidgets>

class dtkWidgetsViewLayoutItem;
class dtkWidgetsViewLayoutPrivate;

class DTKWIDGETS_EXPORT dtkWidgetsViewLayout : public QFrame
{
    Q_OBJECT

public:
     dtkWidgetsViewLayout(QWidget *parent = 0);
    ~dtkWidgetsViewLayout(void);

public:
    dtkWidgetsViewLayoutItem *root(void);
    dtkWidgetsViewLayoutItem *current(void);

public:
    void setCurrent(dtkWidgetsViewLayoutItem *item);

signals:
    void focused(QWidget *view);
    void unfocused(QWidget *view);

public slots:
    void clear(void);

private:
    dtkWidgetsViewLayoutPrivate *d;
};

//
// dtkWidgetsViewLayout.h ends here
