#!/bin/sh

echo "Running test ..."
test=./test/functional_test
testdir=test

$test $testdir/sample.aif

$test $testdir/M1F1-AlawC-AFsp.aif
$test $testdir/M1F1-mulawC-AFsp.aif
$test $testdir/M1F1-int8-AFsp.aif
$test $testdir/M1F1-int8C-AFsp.aif
$test $testdir/M1F1-int12-AFsp.aif
$test $testdir/M1F1-int12C-AFsp.aif
$test $testdir/M1F1-int16-AFsp.aif
$test $testdir/M1F1-int16C-AFsp.aif
$test $testdir/M1F1-int24-AFsp.aif
$test $testdir/M1F1-int24C-AFsp.aif
$test $testdir/M1F1-int32-AFsp.aif
$test $testdir/M1F1-int32C-AFsp.aif
$test $testdir/M1F1-float32C-AFsp.aif
$test $testdir/M1F1-float64C-AFsp.aif

