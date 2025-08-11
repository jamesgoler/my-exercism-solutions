BEGIN {
    name = "you";
}

NF {
    name = $0
}

END {
    printf("One for %s, one for me.", name); 
}