#! /bin/sh
$EXTRACTRC `find . -name \*.ui -o -iname \*.kcfg -o -iname \*.kcfg.cmake` >> rc.cpp || exit 11
$XGETTEXT `find . -name \*.h -o -iname \*.cpp  | grep -v '/tests/' | grep -v '/autotests/'` -o $podir/akonadicontact5.pot
