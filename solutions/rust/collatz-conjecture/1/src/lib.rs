struct Collatz (u64);

impl Iterator for Collatz {
    type Item = u64;

    fn next(&mut self) -> Option<Self::Item> {
        if self.0 > 1 {
            if self.0 % 2 == 0 {
                self.0 >>= 1;
            } else {
                self.0 = (self.0 << 1) + self.0 + 1;
            }
            Some(self.0)
        } else {
            None
        }
    }
}

pub fn collatz(mut n: u64) -> Option<u64> {
    if n > 0 {
        Some(Collatz(n).count() as u64)
    } else {
        None
    }
}
