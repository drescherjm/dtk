#ifndef DTKCONCEPTGENERATOR_H
#define DTKCONCEPTGENERATOR_H

#include <QWizard>
#include <QVariant>

#include "dtkConceptDefinitionPage.h"
#include "dtkNewConceptPage.h"
#include "dtkPluginGeneratorPage.h"
#include "dtkIntroPage.h"

#include "generator.h"

class dtkConceptGenerator : public QWizard
{
public:
    dtkConceptGenerator();
    void accept();

};

#endif // DTKCONCEPTGENERATOR_H
