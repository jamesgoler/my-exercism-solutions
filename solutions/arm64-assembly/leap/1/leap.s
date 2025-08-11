.text
.globl leap_year

leap_year:
        and x1, x0, #3
        cbnz x1, is_not_leap_year

        mov x2, #100
        udiv x1, x0, x2
        mul x1, x1, x2
        sub x1, x0, x1
        cbnz x1, is_leap_year
        
        mov x2, #400
        udiv x1, x0, x2
        mul x1, x1, x2
        sub x1, x0, x1
        cbnz x1, is_not_leap_year

is_leap_year:
        mov x0, #1
        ret
is_not_leap_year:
        mov x0, #0
        ret
