#!/bin/bash

# Version: $Id$
#
#

# Commentary:
#
#

# Change Log:
#
#

# Code:

## #################################################################
## Helper functions
## #################################################################

dtk_formatting_colortext () {
    echo "[38;5;$2m$1[0m"
}

dtk_formatting_green () {
    echo $2 $(dtk_formatting_colortext "$1" "82")
}

dtk_formatting_red () {
    echo $2 $(dtk_formatting_colortext "$1" "196")
}

dtk_formatting_blue () {
    echo $2 $(dtk_formatting_colortext "$1" "27")
}

dtk_formatting_purple () {
    echo $2 $(dtk_formatting_colortext "$1" "141")
}

dtk_formatting_yellow () {
    echo $2 $(dtk_formatting_colortext "$1" "190")
}

dtk_formatting_cyan () {
    echo $2 $(dtk_formatting_colortext "$1" "45")
}

dtk_formatting_clear () {
    echo "$1"
}

dtk_formatting_format () {
    astyle --style=kr                 \
           --indent=spaces=4          \
           --indent-namespaces        \
           --attach-namespaces        \
           --attach-inlines           \
           --attach-extern-c          \
           --break-blocks             \
           --pad-oper                 \
           --align-pointer=name       \
           --align-reference=type     \
           --keep-one-line-statements \
           --convert-tabs             \
           --verbose                  \
           --suffix=none              \
           `find . -type f -name '*.cpp' -or -name '*.tpp' -or -name '*.h'`
}

## #################################################################
## Main
## #################################################################

dtk_formatting_cyan "Checking to see if astyle is installed... " -n
if hash astyle 2>&-
then
    dtk_formatting_green "found."
else
    dtk_formatting_red "not found. Aborting source code formatting!"
    exit 1
fi;

dtk_formatting_format

#
# dtk_formatting.sh ends here
