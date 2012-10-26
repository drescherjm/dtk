### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Mar  9 21:06:43 2009 (+0100)
## Version: $Id$
## Last-Updated: 2012 Fri Oct 26 11:22:24 (+0200)
##           By: Thibaud Kloczko, Inria.
##     Update #: 97
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

## #################################################################
## dtkVariant examples
## #################################################################

add_subdirectory(dtkVariant)

## #################################################################
## dtkLog examples
## #################################################################

add_subdirectory(dtkLogger)
add_subdirectory(dtkLogView)

## #################################################################
## dtkNotification examples
## #################################################################

add_subdirectory(dtkNotificationDisplay)

## #################################################################
## dtkCrypto examples
## #################################################################

add_subdirectory(dtkLicenseManager)

## #################################################################
## dtkCore examples
## #################################################################

add_subdirectory(dtkAbstractDataComposite)
add_subdirectory(dtkReferenceCounting)
add_subdirectory(dtkUpdater)

## #################################################################
## dtkContainer examples
## #################################################################

if(DTK_BUILD_COMPOSER)
  ##add_subdirectory(dtkContainerExample)
endif(DTK_BUILD_COMPOSER)

## #################################################################
## dtkGui examples
## #################################################################

if(DTK_BUILD_SCRIPT)
  add_subdirectory(dtkInterpreter)
endif(DTK_BUILD_SCRIPT)

add_subdirectory(dtkTagCloud)
add_subdirectory(dtkTextEditor)
add_subdirectory(dtkSettingsEditor)
add_subdirectory(dtkFinder)
add_subdirectory(dtkAboutPlugin)
add_subdirectory(dtkFlowLayout)
add_subdirectory(dtkViewManager)

## #################################################################
## dtkVr examples
## #################################################################

if(DTK_BUILD_VR)
  add_subdirectory(dtkVrGestureRecognizer)
endif(DTK_BUILD_VR)

## #################################################################
## dtkPlot examples
## #################################################################

if(DTK_BUILD_PLOT)
  add_subdirectory(dtkPlotEcg)
endif(DTK_BUILD_PLOT)

## #################################################################
## dtkComposer examples
## #################################################################

if(DTK_BUILD_COMPOSER)
  ##add_subdirectory(dtkComposerTransmitter)
endif(DTK_BUILD_COMPOSER)
