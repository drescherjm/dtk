### dtkDart.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Jan  8 15:59:24 2010 (+0100)
## Version: $Id$
## Last-Updated: Fri Apr  2 09:29:13 2010 (+0200)
##           By: Julien Wintz
##     Update #: 8
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

mark_as_advanced(DART_ROOT)

set(CTEST_PROJECT_NAME "dtk")
set(CTEST_UPDATE_TYPE "git")
set(UPDATE_COMMAND "git")
set(UPDATE_TYPE "git")
set(NIGHTLY_START_TIME "21:00:00 EST")
set(DROP_METHOD "http")
set(DROP_SITE "cdash.inria.fr")
set(DROP_LOCATION "/CDash/submit.php?project=dtk")
set(DROP_SITE_CDASH TRUE)

include(Dart)
