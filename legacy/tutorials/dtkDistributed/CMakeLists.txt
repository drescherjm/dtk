### CMakeLists.txt --- 
## 
## Author: 
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Thu Sep  8 09:45:54 2011 (+0200)
## Version: $Id$
## Last-Updated: Tue Sep 18 10:49:08 2012 (+0200)
##           By: Julien Wintz
##     Update #: 22
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

add_subdirectory(0)

if(DTK_HAVE_MPI)

add_subdirectory(1)

if(DTK_BUILD_COMPOSER)
add_subdirectory(2)
add_subdirectory(3)
add_subdirectory(4)
add_subdirectory(5)
add_subdirectory(6)
endif(DTK_BUILD_COMPOSER)

endif(DTK_HAVE_MPI)
