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
    class dtkConceptDefinitionPage;
}

class dtkConceptDefinitionPage : public QWizardPage
{
    Q_OBJECT

public:
     dtkConceptDefinitionPage(QWidget *parent = 0);
    ~dtkConceptDefinitionPage();

private:
    Ui::dtkConceptDefinitionPage *ui;
};

//
// dtkConceptDefinitionPage.h ends here
