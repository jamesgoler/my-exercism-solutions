pub fn factors(mut n: u64) -> Vec<u64> {
    let mut result = vec![];
    let mut current = 2;
    while n > 1 {
        if n % current == 0 {
            n /= current;
            result.push(current);
        } else {
            current += 1;
        }
    }
    result
}
