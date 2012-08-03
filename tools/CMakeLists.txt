### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Mar  9 21:06:43 2009 (+0100)
## Version: $Id$
## Last-Updated: Fri Aug  3 14:06:28 2012 (+0200)
##           By: tkloczko
##     Update #: 21
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

add_subdirectory(dtkCreator)
add_subdirectory(dtkDeploy)
add_subdirectory(dtkTestGenerator)
add_subdirectory(dtkPluginGenerator)
add_subdirectory(dtksh)
add_subdirectory(dtkHeadersBuilder)
add_subdirectory(dtkHeadersMover)
add_subdirectory(dtkComposerEvaluator)
# if(MPI_FOUND)
# add_subdirectory(dtkComposerEvaluatorSlave)
# endif(MPI_FOUND)
# add_subdirectory(dtkDistributedServer)
