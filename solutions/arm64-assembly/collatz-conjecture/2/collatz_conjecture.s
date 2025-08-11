.equ INVALID_NUMBER, -1

.text
.globl steps

steps:
        mov w1, INVALID_NUMBER
        mov x3, #3
        cmp x0, #1
        b.lt loop_end
        
loop_start:
        add w1, w1, #1
        cmp x0, #1
        b.le loop_end

        and x2, x0, #1
        cbz x2, if_even
        mul x0, x0, x3
        add x0, x0, #1
        b loop_start
if_even:
        ASR x0, x0, #1
        b loop_start

loop_end:
        mov w0, w1
        ret
