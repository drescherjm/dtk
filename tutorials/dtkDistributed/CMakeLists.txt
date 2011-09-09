### CMakeLists.txt --- 
## 
## Author: 
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Thu Sep  8 09:45:54 2011 (+0200)
## Version: $Id$
## Last-Updated: Thu Sep  8 10:38:57 2011 (+0200)
##           By: jwintz
##     Update #: 7
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

endif(DTK_HAVE_MPI)
