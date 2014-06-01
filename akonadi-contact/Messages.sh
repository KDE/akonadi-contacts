#! /bin/sh
$EXTRACTRC src/*.ui src/actions/*.kcfg.cmake src/*.kcfg >> rc.cpp || exit 11
$XGETTEXT src/*.cpp src/*.h src/actions/*.cpp src/editor/*.cpp src/editor/im/*.cpp -o $podir/akonadicontact5.pot
rm -f rc.cpp
