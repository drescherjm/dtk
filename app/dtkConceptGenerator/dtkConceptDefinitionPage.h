#ifndef dtkConceptDefinitionPage_H
#define dtkConceptDefinitionPage_H

#include <QWizardPage>

namespace Ui {
class dtkConceptDefinitionPage;
}

class dtkConceptDefinitionPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit dtkConceptDefinitionPage(QWidget *parent = 0);
    ~dtkConceptDefinitionPage();

private:
    Ui::dtkConceptDefinitionPage *ui;
};

#endif // dtkConceptDefinitionPage_H
