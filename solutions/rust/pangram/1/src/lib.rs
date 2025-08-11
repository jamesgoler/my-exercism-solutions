/// Determine whether a sentence is a pangram.
pub fn is_pangram(sentence: &str) -> bool {
    let mut seen = (1 << 26) - 1;
    for c in sentence.chars().filter(|c| c.is_ascii_alphabetic()) {
        let i = 1 << (c.to_ascii_lowercase() as u8 - b'a');
        seen &= !i;
        if seen == 0 {
            return true;
        }
    }
    false
}
