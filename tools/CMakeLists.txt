### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Mar  9 21:06:43 2009 (+0100)
## Version: $Id$
## Last-Updated: Tue Sep 18 10:47:22 2012 (+0200)
##           By: Julien Wintz
##     Update #: 29
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

add_subdirectory(dtkDeploy)
add_subdirectory(dtkTestGenerator)
add_subdirectory(dtkPluginGenerator)
add_subdirectory(dtkHeadersBuilder)
add_subdirectory(dtkHeadersMover)

if(DTK_BUILD_SCRIPT)
  add_subdirectory(dtksh)
endif(DTK_BUILD_SCRIPT)

if(DTK_BUILD_COMPOSER)
  add_subdirectory(dtkComposerEvaluator)
endif(DTK_BUILD_COMPOSER)

if(MPI_FOUND AND DTK_BUILD_DISTRIBUTED AND DTK_BUILD_COMPOSER)
  add_subdirectory(dtkComposerEvaluatorSlave)
endif(MPI_FOUND AND DTK_BUILD_DISTRIBUTED AND DTK_BUILD_COMPOSER)

if(DTK_BUILD_DISTRIBUTED AND DTK_BUILD_COMPOSER)
  add_subdirectory(dtkDistributedServer)
endif(DTK_BUILD_DISTRIBUTED AND DTK_BUILD_COMPOSER)

if(DTK_BUILD_COMPOSER AND DTK_BUILD_DISTRIBUTED)
  add_subdirectory(dtkCreator)
endif(DTK_BUILD_COMPOSER AND DTK_BUILD_DISTRIBUTED)
