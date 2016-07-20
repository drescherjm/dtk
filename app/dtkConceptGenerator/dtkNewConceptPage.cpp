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

#include     "dtkNewConceptPage.h"
#include "ui_dtkNewConceptPage.h"

dtkNewConceptPage::dtkNewConceptPage(QWidget *parent) : QWizardPage(parent), ui(new Ui::dtkNewConceptPage)
{
    ui->setupUi(this);
    registerField("new.layer", ui->m_layer);
    registerField("new.namespace", ui->m_namespace);
    registerField("new.prefix", ui->m_prefix);
    registerField("new.name", ui->m_name);

}

dtkNewConceptPage::~dtkNewConceptPage()
{
    delete ui;
}

//
// dtkNewConceptPage.cpp ends here
