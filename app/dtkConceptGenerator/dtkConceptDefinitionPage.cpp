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

#include    "dtkConceptDefinitionPage.h"
#include "ui_dtkConceptDefinitionPage.h"

dtkConceptDefinitionPage::dtkConceptDefinitionPage(QWidget *parent) : QWizardPage(parent), ui(new Ui::dtkConceptDefinitionPage)
{
    this->ui->setupUi(this);
    this->registerField("def.runnable", ui->m_runnable);
    this->registerField("def.qObject", ui->m_qObject);
    this->registerField("def.custom", ui->m_custom);
    this->registerField("def.customName", ui->m_customName);
    this->registerField("def.pluginSystem", ui->m_pluginSystem);
}

dtkConceptDefinitionPage::~dtkConceptDefinitionPage(void)
{
    delete this->ui;
}

//
// dtkConceptDefinitionPage.cpp ends here
