#include "dtkConceptDefinitionPage.h"
#include "ui_dtkConceptDefinitionPage.h"

dtkConceptDefinitionPage::dtkConceptDefinitionPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::dtkConceptDefinitionPage)
{
    ui->setupUi(this);
    registerField("def.runnable",ui->m_runnable);
    registerField("def.qObject",ui->m_qObject);
    registerField("def.custom",ui->m_custom);
    registerField("def.customName",ui->m_customName);
    registerField("def.pluginSystem",ui->m_pluginSystem);

}

dtkConceptDefinitionPage::~dtkConceptDefinitionPage()
{
    delete ui;
}
