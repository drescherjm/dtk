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

#pragma once

#include "dtkWidgetsExport.h"

#include <QtCore>

class DTKWIDGETS_EXPORT dtkWidgetsViewController : public QObject
{
    Q_OBJECT

public:
    static dtkWidgetsViewController *instance(void);

public:
    void insert(const QString& name, QWidget *view);

public:
    QWidget *view(const QString& name);
    QStringList viewNames(void);

signals:
    void inserted(QWidget *, const QString& name);

protected:
     dtkWidgetsViewController(void);
    ~dtkWidgetsViewController(void);

private:
    static dtkWidgetsViewController *s_instance;

private:
    class dtkWidgetsViewControllerPrivate *d;
};

//
// dtkWidgetsViewController.h ends here
