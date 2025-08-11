BEGIN {
    name = "you";
}

{
    gsub(/[^[:alnum:][:space:]-]/, "", $0);
    n = split($0, a, /[[:space:]-]+/);
    for (i = 1; i <= n; i++)
        printf toupper(substr(a[i], 1, 1));
}
