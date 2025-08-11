pub fn check(candidate: &str) -> bool {
    let mut seen = 0;
    for c in candidate.chars().filter(|c| c.is_ascii_alphabetic()) {
        let i = 1 <<(c.to_ascii_lowercase() as u8 - b'a');
        if seen & i != 0 {
            return false;
        }
        seen |= i;
    }
    true
}
