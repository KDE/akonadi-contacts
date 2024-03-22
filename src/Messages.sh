#! /bin/sh
# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
$EXTRACTRC `find . -name \*.ui` >> rc.cpp || exit 11
$XGETTEXT `find . -name \*.h -o -iname \*.cpp  | grep -v '/tests/' | grep -v '/autotests/'` -o $podir/akonadicontact6.pot
