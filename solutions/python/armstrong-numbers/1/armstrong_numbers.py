import math

def is_armstrong_number(number) -> bool:
    if number == 0:
        return True

    digits_num = math.ceil(math.log(number, 10))
    sum = 0
    tmp = number
    for _ in range(0, digits_num):
        d = tmp % 10
        tmp //= 10
        sum += d ** digits_num
    return sum == number