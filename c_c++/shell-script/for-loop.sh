#!/bin/bash
# see: http://www.macs.hw.ac.uk/~hwloidl/Courses/LinuxIntro/x864.html
# Counting the number of lines in a list of files for loop over arguments

# see: https://www.tutorialspoint.com/unix/unix-special-variables.htm
# see: https://www.tutorialspoint.com/unix/unix-regular-expressions.htm
# $# -> number of arguments supplied to the script 
# sed -> stream editor, goes directly to STDOUT without changing input file


if [ $# -lt 1 ] # if number of arguments supplied to the script less than 1
then
  echo "Usage: $0 file ..."
  exit 1
fi

echo "$0 counts the lines of code" 
l=0
n=0
s=0
for f in $* # for all the arugments supplied
do
	l=`wc -l $f | sed 's/^\([0-9]*\).*$/\1/'` #  count number of lines
	echo "$f: $l"
        n=$[ $n + 1 ]
        s=$[ $s + $l ]
done

echo "$n files in total, with $s lines in total"