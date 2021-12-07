#! /bin/sh
# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
$EXTRACTRC *.ui >> rc.cpp
$XGETTEXT *.cpp  -o $podir/kcm_akonadicontact_actions.pot
