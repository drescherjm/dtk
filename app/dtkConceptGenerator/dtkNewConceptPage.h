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
    class dtkNewConceptPage;
}

class dtkNewConceptPage : public QWizardPage
{
    Q_OBJECT

public:
     dtkNewConceptPage(QWidget *parent = 0);
    ~dtkNewConceptPage(void);

private:
    Ui::dtkNewConceptPage *ui;
};

//
// dtkNewConceptPage.h ends here
