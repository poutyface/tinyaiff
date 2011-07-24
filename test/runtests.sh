#!/bin/sh

echo "Running test ..."

for i in test/*_test
do
  echo [ $i ] =========================== $'\n'
  if [ -e $i ] ; then
    if ./$i ; then
      echo ""
      echo $i, PASS $'\n'
    else
      echo ""
      echo $i, FAIL $'\n'
    fi
  fi
done
