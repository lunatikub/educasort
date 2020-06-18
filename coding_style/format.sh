#!/bin/bash

SCRIPT_DIR=$(dirname $(readlink -f $0))
SCRIPT_NAME=$(basename $(readlink -f $0))
ROOT_DIR=${SCRIPT_DIR}/../

source ${ROOT_DIR}/tools/scripts/utils.sh
source ${ROOT_DIR}/tools/scripts/color.sh

CLANG_FMT=$(which clang-format-9)
if [ $? -ne 0 ]; then
    err $LINENO  "[!] clang-format not installed. Unable to check source file format policy."
    return -1
fi

cp ${SCRIPT_DIR}/clang-format ${ROOT_DIR}/.clang-format

c_dir_list=(
    src
    include
    unit-tests
)

pushd ${ROOT_DIR} >/dev/null 2>&1
{
    # C/C++ coding style
    ret_c=0
    for dir in ${c_dir_list[@]}
    do
        printf "${color[purple]}[dir]${color[reset]} $dir\n"
        for file in $(find ${ROOT_DIR}/${dir} -regex ".*\.[c|h][c|h]?")
        do
            printf "${color[cyan]} [file]${color[reset]} $(basename $file)"
            clang-format --output-replacements-xml $file | grep -q offset
            [ $? -ne 0 ] && printf "${color[green]} [OK]\n" || printf "${color[red]} [updated]\n"
            clang-format --style=file -i $file
        done
    done
}
popd >/dev/null 2>&1

exit 0
