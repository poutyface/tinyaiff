#!/bin/bash

echo "Running test ..."
test=./test/functional_test
loop_test=./test/loop_test
inputdir=test/input
outputdir=test/output

check_succeed() {
    if [ $? -eq 0 ]; then echo "PASS"; else echo "FAIL"; fi
    echo "----------"
}

check_fail() {
    if [ $? -ne 0 ]; then echo "PASS"; else echo "FAIL"; fi
    echo "----------"
}


$test $inputdir/test.aif $outputdir/test.data; check_succeed

$test $inputdir/M1F1-AlawC-AFsp.aif $outputdir/M1F1-AlawC-AFsp.data; check_succeed
$test $inputdir/M1F1-mulawC-AFsp.aif $outputdir/M1F1-mulawC-AFsp.data; check_succeed
$test $inputdir/M1F1-int8-AFsp.aif $outputdir/M1F1-int8-AFsp.data; check_succeed
$test $inputdir/M1F1-int8C-AFsp.aif $outputdir/M1F1-int8C-AFsp.data; check_succeed
$test $inputdir/M1F1-int12-AFsp.aif $outputdir/M1F1-int12-AFsp.data; check_succeed
$test $inputdir/M1F1-int12C-AFsp.aif $outputdir/M1F1-int12C-AFsp.data; check_succeed
$test $inputdir/M1F1-int16-AFsp.aif $outputdir/M1F1-int16-AFsp.data; check_succeed
$test $inputdir/M1F1-int16C-AFsp.aif $outputdir/M1F1-int16C-AFsp.data; check_succeed
$test $inputdir/M1F1-int24-AFsp.aif $outputdir/M1F1-int24-AFsp.data; check_succeed
$test $inputdir/M1F1-int24C-AFsp.aif $outputdir/M1F1-int24C-AFsp.data; check_succeed
$test $inputdir/M1F1-int32-AFsp.aif $outputdir/M1F1-int32-AFsp.data; check_succeed
$test $inputdir/M1F1-int32C-AFsp.aif $outputdir/M1F1-int32C-AFsp.data; check_succeed
$test $inputdir/M1F1-float32C-AFsp.aif $outputdir/M1F1-float32C-AFsp.data; check_succeed
$test $inputdir/M1F1-float64C-AFsp.aif $outputdir/M1F1-float64C-AFsp.data; check_succeed

$test $inputdir/Pmiscck.aif $outputdir/Pmiscck.data; check_succeed
$test $inputdir/Pnossnd.aif $outputdir/Pnossnd.data; check_succeed
$test $inputdir/Poffset.aif $outputdir/Poffset.data; check_succeed
$test $inputdir/Porder.aif $outputdir/Porder.data; check_fail
$test $inputdir/Ptjunk.aif $outputdir/Ptjunk.data; check_succeed

$test $inputdir/Fnonull.aif $outputdir/Fnonull.data; check_succeed

$test $inputdir/aiff-16.snd $outputdir/aiff-16.data; check_succeed
$test $inputdir/aiff-8.snd $outputdir/aiff-8.data; check_succeed
$test $inputdir/alaw.aifc $outputdir/alaw.data; check_succeed
$test $inputdir/ulaw.aifc $outputdir/ulaw.data; check_succeed
$test $inputdir/g722.aifc $outputdir/g722.data; check_succeed
$test $inputdir/o2_726.aiff $outputdir/o2_726.data; check_succeed
$test $inputdir/o2_728.aiff $outputdir/o2_728.data; check_succeed
$test $inputdir/o2_gsm.aiff $outputdir/o2_gsm.data; check_succeed
$test $inputdir/wood12.aiff $outputdir/wood12.data; check_succeed
$test $inputdir/wood24.aiff $outputdir/wood24.data; check_succeed
$test $inputdir/digit0v0.aiff $outputdir/digit0v0.data; check_fail

$loop_test $inputdir/test.aif $outputdir/loop_test.data; check_succeed
