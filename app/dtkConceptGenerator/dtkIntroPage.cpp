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

#include    "dtkIntroPage.h"
#include "ui_dtkIntroPage.h"

dtkIntroPage::dtkIntroPage(QWidget *parent) : QWizardPage(parent), ui(new Ui::dtkIntroPage)
{
    this->ui->setupUi(this);
    this->registerField("intro.path", ui->m_path);
    this->connect(ui->m_browse, SIGNAL(clicked(bool)), this, SLOT(browse()));
}

void dtkIntroPage::browse(void)
{
    this->ui->m_path->setText(QFileDialog::getExistingDirectory(this, "Save"));
}

dtkIntroPage::~dtkIntroPage(void)
{
    delete this->ui;
}

//
// dtkIntroPage.cpp ends here
