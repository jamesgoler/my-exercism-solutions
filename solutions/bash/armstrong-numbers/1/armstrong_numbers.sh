#!/usr/bin/env bash

function main() {
    local tmp=$1
    local input=$1
    local len=${#input}
    local armstrong=0
    while [ $tmp -ne 0 ]; do
        (( d = tmp % 10 ))
        (( tmp /= 10 ))
        (( armstrong += d ** len ))
    done
    if [ $armstrong -eq $input ]; then
        echo "true"
    else
        echo "false"
    fi
}

main "$@"