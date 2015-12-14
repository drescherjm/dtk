#ifndef DTKCONCEPTGENERATOR_H
#define DTKCONCEPTGENERATOR_H

#include <QWizard>
#include "dtkConceptDefinitionPage.h"
#include "dtkNewConceptPage.h"
#include "dtkPluginGeneratorPage.h"

class dtkConceptGenerator : public QWizard
{
public:
    dtkConceptGenerator();
};

#endif // DTKCONCEPTGENERATOR_H
