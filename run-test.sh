#!/bin/bash

local total=0
local fail=()
local success=()

workdir=$(cd $(dirname $0); pwd)

allTest=$(find test/ -name "*.run")

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${workdir}/glib

export LD_LIBRARY_PATH

echo "当前目录下所有测试用例:${allTest}"

for element in ${allTest[@]}
do
    $element
    if [[ $? -eq 0 ]];then
        success+=($element)
    else
        fail+=($element)
    fi
    (( total+=1 ))
done

echo "######################### 测试结果 #########################"
echo "总共测试:${total}"
echo "测试失败:${#fail[@]}"
echo "测试通过:${#success[@]}"
echo "失败的测试:${fail}"
echo "###########################################################"

