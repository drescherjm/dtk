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

#include "dtkComposerExport.h"

#include <QtCore>

class DTKCOMPOSER_EXPORT dtkComposerViewController : public QObject
{
    Q_OBJECT

public:
    static dtkComposerViewController *instance(void);

public:
    void insert(const QString& name, QWidget *view);

public:
    QWidget *view(const QString& name);
    QStringList viewNames(void);

signals:
    void inserted(QWidget *, const QString&);

protected:
     dtkComposerViewController(void);
    ~dtkComposerViewController(void);

private:
    static dtkComposerViewController *s_instance;

private:
    class dtkComposerViewControllerPrivate *d;
};

//
// dtkComposerViewController.h ends here
