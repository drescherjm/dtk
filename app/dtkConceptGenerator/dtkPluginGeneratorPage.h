#ifndef DTKPLUGINGENERATORPAGE_H
#define DTKPLUGINGENERATORPAGE_H

#include <QWizardPage>

namespace Ui {
class dtkPluginGeneratorPage;
}

class dtkPluginGeneratorPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit dtkPluginGeneratorPage(QWidget *parent = 0);
    ~dtkPluginGeneratorPage();

private:
    Ui::dtkPluginGeneratorPage *ui;
};

#endif // DTKPLUGINGENERATORPAGE_H
