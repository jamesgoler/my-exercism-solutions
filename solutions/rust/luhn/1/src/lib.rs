/// Check a Luhn checksum.
pub fn is_valid(code: &str) -> bool {
    if code.len() <= 1 {
        return false;
    }
    let double_map = [0, 2, 4, 6, 8, 1, 3, 5, 7, 9];
    let mut sum = 0;
    let mut count = 0;
    for c in code.as_bytes().iter().rev() {
        if c.is_ascii_whitespace() {
            continue;
        }
        if !c.is_ascii_digit() {
            return false;
        }
        count += 1;
        let mut d = c - b'0';
        if count % 2 == 0 {
            d = double_map[d as usize];
        }
        sum = (sum + d) % 10; // avoid overflowing.
    }
    count > 1 && sum % 10 == 0
}
