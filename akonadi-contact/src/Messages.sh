#! /bin/sh
$EXTRACTRC `find . -name \*.ui -o -iname \*.kcfg -o -iname \*.kcfg.cmake` >> rc.cpp || exit 11
$XGETTEXT `find . -name \*.h -o -iname \*.cpp` -o $podir/akonadicontact5.pot
rm -f rc.cpp
