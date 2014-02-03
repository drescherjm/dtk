### CMakeLists.txt --- 
## 
## Author: 
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Thu Sep  8 09:45:36 2011 (+0200)
## Version: $Id$
## Last-Updated: Tue Sep 18 09:28:27 2012 (+0200)
##           By: Julien Wintz
##     Update #: 10
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

if(DTK_BUILD_DISTRIBUTED)
  add_subdirectory(dtkDistributed)
endif(DTK_BUILD_DISTRIBUTED)
