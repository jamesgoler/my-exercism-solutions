.equ INVALID_NUMBER, -1

.text
.globl steps

steps:
        mov w1, INVALID_NUMBER
        cmp x0, #1
        b.lt loop_end
loop_start:
        add w1, w1, #1
        cmp x0, #1
        b.le loop_end
if_start:
        and x2, x0, #1
        cbz x2, if_even
if_odd:
        lsl x3, x0, #1
        ADD x0, x3, x0
        ADD x0, x0, #1
        b if_end
if_even:
        ASR x0, x0, #1
if_end:
        b loop_start
loop_end:
        mov w0, w1
        ret
