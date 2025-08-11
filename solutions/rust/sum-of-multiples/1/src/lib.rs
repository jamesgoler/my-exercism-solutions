use std::collections::HashSet;

pub fn sum_of_multiples(limit: u32, factors: &[u32]) -> u32 {
    let mut set = HashSet::new();
    let mut sum = 0;
    for base in factors.iter().cloned().filter(|base| *base > 0) {
        let mut n = base;
        while n < limit {
            if set.insert(n) {
                sum += n;
            }
            n += base;
        }
    }
    sum
}
