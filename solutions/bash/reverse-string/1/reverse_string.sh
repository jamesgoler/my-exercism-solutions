#!/usr/bin/env bash

function main {
    echo "$@" | rev
}

main "$@"