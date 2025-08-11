pub fn series(digits: &str, len: usize) -> Vec<String> {
    digits.as_bytes()
          .windows(len)
          .map(|w| unsafe { String::from_utf8_unchecked(w.to_vec()) })
          .collect()
}
