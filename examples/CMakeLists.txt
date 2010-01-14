### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Mar  9 21:06:43 2009 (+0100)
## Version: $Id$
## Last-Updated: Thu Jan 14 11:20:31 2010 (+0100)
##           By: Julien Wintz
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

add_subdirectory(dtkInterpreter)
add_subdirectory(dtkLog)
add_subdirectory(dtkTagCloud)
add_subdirectory(dtkTextEditor)
add_subdirectory(dtkUpdater)
add_subdirectory(dtkSearchBar)
add_subdirectory(dtkSettingsEditor)

if(OPENSSL_FOUND)
add_subdirectory(dtkLicenseManager)
endif(OPENSSL_FOUND)
