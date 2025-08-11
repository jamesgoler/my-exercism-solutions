#!/usr/bin/env bash

function main () {
    name="you"
    if [ $# -ne 0 ]; then
        name="$1"
    fi

    echo "One for ${name}, one for me."
}

main "$@"