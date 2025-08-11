BEGIN {
    name = "you";
}

{
    if (NF > 0) {
        name = $0
    }
}

END {
    printf("One for %s, one for me.", name); 
}