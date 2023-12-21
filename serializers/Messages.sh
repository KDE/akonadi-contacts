#!/bin/sh
$XGETTEXT `find . -name \*.cpp | grep -v '/autotests/'` -o $podir/akonadicontact6-serializer.pot


