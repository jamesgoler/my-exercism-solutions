#!/usr/bin/env bash

function main () {
    echo "One for ${1:-you}, one for me."
}

main "$@"