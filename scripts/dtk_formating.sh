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

dtk_formating_colortext () {
    echo "[38;5;$2m$1[0m"
}

dtk_formating_green () {
    echo $(dtk_formating_colortext "$1" "82")
}

dtk_formating_red () {
    echo $(dtk_formating_colortext "$1" "196")
}

dtk_formating_blue () {
    echo $(dtk_formating_colortext "$1" "27")
}

dtk_formating_purple () {
    echo $(dtk_formating_colortext "$1" "141")
}

dtk_formating_yellow () {
    echo $(dtk_formating_colortext "$1" "190")
}

dtk_formating_cyan () {
    echo $(dtk_formating_colortext "$1" "45")
}

dtk_formating_clear () {
    echo "$1"
}

dtk_formating_format () {
    astyle --indent=spaces=4 --style=linux                       \
           --indent-labels --pad-oper --unpad-paren --pad-header \
           --keep-one-line-statements --convert-tabs             \
           --indent-preprocessor                                 \
           `find -type f -name '*.cpp' -or name '*.tpp' -name -or -name '*.h'`
}


## #################################################################
## Main
## #################################################################

dtk_formating_cyan "Checking to see if astyle is installed..."
if hash astyle 2>&-
then
    dtk_formating_green "found."
else
    dtk_formating_red "not found. Aborting installation!"
    exit 1
fi;

dtk_formating_format

#
# dtk_formatting.sh ends here
