### CMakeLists.txt --- 
## 
## Author: 
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Thu Sep  8 09:45:54 2011 (+0200)
## Version: $Id$
## Last-Updated: Mon Sep 12 10:07:13 2011 (+0200)
##           By: Julien Wintz
##     Update #: 11
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
add_subdirectory(2)
add_subdirectory(3)

endif(DTK_HAVE_MPI)
