### CMakeLists.txt --- 
## 
## Author: 
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Thu Sep  8 09:45:54 2011 (+0200)
## Version: $Id$
## Last-Updated: Fri Sep  9 10:24:59 2011 (+0200)
##           By: jwintz
##     Update #: 9
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

endif(DTK_HAVE_MPI)
