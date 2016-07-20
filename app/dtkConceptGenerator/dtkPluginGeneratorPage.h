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
    class dtkPluginGeneratorPage;
}

class dtkPluginGeneratorPage : public QWizardPage
{
    Q_OBJECT

public:
     dtkPluginGeneratorPage(QWidget *parent = 0);
    ~dtkPluginGeneratorPage(void);

protected:
    void initializePage(void);

public slots:
    void refresh(void);


private:
    Ui::dtkPluginGeneratorPage *ui;
};

//
// dtkPluginGeneratorPage.h ends here
