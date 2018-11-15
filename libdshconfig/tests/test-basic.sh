#! /bin/sh
# Basic testing program for dshconfig
# read a config file, and output the file processed.

set -ex

./test-dshconfig < ${srcdir}/tests/test-basic.input > tests-basic.o
diff ${srcdir}/tests/test-basic.output tests-basic.o
rm -f tests-basic.o
