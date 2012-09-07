### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Mar  9 21:06:43 2009 (+0100)
## Version: $Id$
## Last-Updated: Mon Jul 16 09:59:05 2012 (+0200)
##           By: tkloczko
##     Update #: 88
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

add_subdirectory(dtkContainerExample)

## #################################################################
## dtkGui examples
## #################################################################

add_subdirectory(dtkInterpreter)
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

add_subdirectory(dtkVrGestureRecognizer)

## #################################################################
## dtkPlot examples
## #################################################################

add_subdirectory(dtkPlotEcg)

## #################################################################
## dtkComposer examples
## #################################################################

add_subdirectory(dtkComposerTransmitter)
