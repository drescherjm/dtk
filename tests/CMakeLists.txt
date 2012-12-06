### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Tue Jun 19 18:23:41 2012 (+0200)
## Version: $Id$
## Last-Updated: 2012 Mon Nov 19 15:45:24 (+0100)
##           By: Thibaud Kloczko
##     Update #: 5
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

add_subdirectory(dtkMath)
add_subdirectory(dtkCore)

if(DTK_BUILD_ZIP)
  add_subdirectory(dtkZip)
endif(DTK_BUILD_ZIP)
