#!/usr/bin/env bash

function main() {
    local score=$1
    local command=$2
    if [[ "$command" == 'allergic_to' ]]; then
        if [[ "$(list_allergies "$score")" == *"$3"* ]]; then
            echo "true"
        else
            echo "false"
        fi
    elif [[ "$command" == 'list' ]]; then
        list_allergies "$score"
    fi
}

function list_allergies() {
    local score=$1
    local result
    result+=" "$(echo_if_has "$score" 1   'eggs')
    result+=" "$(echo_if_has "$score" 2   'peanuts')
    result+=" "$(echo_if_has "$score" 4   'shellfish')
    result+=" "$(echo_if_has "$score" 8   'strawberries')
    result+=" "$(echo_if_has "$score" 16  'tomatoes')
    result+=" "$(echo_if_has "$score" 32  'chocolate')
    result+=" "$(echo_if_has "$score" 64  'pollen')
    result+=" "$(echo_if_has "$score" 128 'cats')
    # shellcheck disable=SC2086
    echo $result
}

function echo_if_has() {
    local score=$1
    local value=$2
    local allergy=$3
    if (( score & value )); then
        echo "$allergy"
    else
        echo ""
    fi
}

main "$@"
