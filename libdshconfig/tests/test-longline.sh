#! /bin/sh
# try using some perl to run this test.
set -e
perl -e 'print ("x"x299900 . ": " . "y"x299900 . "\n")x20 ' | ./test-dshconfig > /dev/null