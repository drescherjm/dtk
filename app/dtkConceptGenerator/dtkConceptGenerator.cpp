#include "dtkConceptGenerator.h"

dtkConceptGenerator::dtkConceptGenerator()
{
      addPage(new dtkNewConceptPage());
      addPage(new dtkConceptDefinitionPage());
      addPage(new dtkPluginGeneratorPage());
}

