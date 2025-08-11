#[inline(always)]
fn is_question(message: &str) -> bool {
    message.ends_with('?')
}

#[inline(always)]
fn is_yelling(message: &str) -> bool {
    let mut alpha_count = 0;
    for ch in message.chars().filter(|ch| ch.is_alphabetic()) {
        if !ch.is_uppercase() {
            return false;
        }
        alpha_count += 1;
    }
    alpha_count > 0
}

#[inline(always)]
fn is_silence(message: &str) -> bool {
    message.is_empty()
}

pub fn reply(message: &str) -> &str {
    let message = message.trim();
    if is_silence(message) {
        "Fine. Be that way!"
    } else if is_question(message) {
        if is_yelling(message) {
            "Calm down, I know what I'm doing!"
        } else {
            "Sure."
        }
    } else if is_yelling(message) {
        "Whoa, chill out!"
    } else {
        "Whatever."
    }
}
