pub fn abbreviate(phrase: &str) -> String {
    let mut result = String::new();

    let mut last_ch = ' ';
    let mut pick = true;
    for ch in phrase.chars() {
        if ch == '-' || ch.is_whitespace() {
            pick = true;
        } else if (!last_ch.is_uppercase() && ch.is_uppercase()) ||
                  (pick && !ch.is_ascii_punctuation())
        {
            for ch in ch.to_uppercase() {
                result.push(ch);
            }
            pick = false;
        }
        last_ch = ch;
    }

    result
}
