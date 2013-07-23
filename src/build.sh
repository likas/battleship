#!/bin/sh


aclocal
autoheader
autoreconf -i --force
automake --add-missing
