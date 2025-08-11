pub fn brackets_are_balanced(string: &str) -> bool {
    let mut stack = vec![];

    for ch in string.chars() {
        if let Some(op) = opening(ch) {
            if stack.is_empty() || op != stack.pop().unwrap() {
                return false;
            }
        } else if matches!(ch, '(' | '[' | '{') {
            stack.push(ch);
        }
    }
    stack.is_empty()
}

#[inline(always)]
fn opening(ch: char) -> Option<char> {
    match ch {
        ')' => Some('('),
        ']' => Some('['),
        '}' => Some('{'),
        _ => None,
    }
}