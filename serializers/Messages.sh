#!/bin/sh
$XGETTEXT `find . -name \*.cpp | grep -v '/autotests/'` -o $podir/akonadicontact5-serializer.pot


