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

#include <QtWidgets>

namespace Ui {
    class dtkIntroPage;
}

class dtkIntroPage : public QWizardPage
{
    Q_OBJECT

public:
     dtkIntroPage(QWidget *parent = 0);
    ~dtkIntroPage(void);

public slots:
    void browse(void);

signals:
    void generatorSet(QString);

private:
    Ui::dtkIntroPage *ui;
};

//
// dtkIntroPage.h ends here
