### CMakeLists.txt --- 
## 
## Author: 
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Thu Sep  8 09:45:54 2011 (+0200)
## Version: $Id$
## Last-Updated: Wed Sep 14 13:20:35 2011 (+0200)
##           By: Julien Wintz
##     Update #: 13
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
add_subdirectory(4)

endif(DTK_HAVE_MPI)
