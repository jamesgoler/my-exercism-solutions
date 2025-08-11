pub fn nth(n: u32) -> u32 {
    let mut current = 2;
    for i in 0..n {
        current = next_prime(current);
    }
    current
}

#[inline(always)]
fn next_prime(mut n: u32) -> u32 {
    loop {
        n += 1;
        if is_prime(n) {
            break;
        }
    }
    n
}

#[inline(always)]
fn is_prime(n: u32) -> bool {
    let nsqrt = n.isqrt();
    for i in 2..=nsqrt {
        if n % i == 0 {
            return false;
        }
    }
    true
}