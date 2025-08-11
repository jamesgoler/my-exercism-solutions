def steps(number):
    if number < 1:
        raise ValueError("Only positive integers are allowed")
    s = 0
    while number != 1:
        if number % 2 == 0:
            number >>= 1
        else:
            number = (number << 1) + number + 1
        s += 1
    return s
        
