#ifndef DTKNEWCONCEPTPAGE_H
#define DTKNEWCONCEPTPAGE_H

#include <QWizardPage>

namespace Ui {
class dtkNewConceptPage;
}

class dtkNewConceptPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit dtkNewConceptPage(QWidget *parent = 0);
    ~dtkNewConceptPage();

private:
    Ui::dtkNewConceptPage *ui;
};

#endif // DTKNEWCONCEPTPAGE_H
