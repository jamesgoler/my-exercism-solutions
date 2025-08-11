pub fn recite(start_bottles: u32, take_down: u32) -> String {
    let mut result = String::new();
    
    for i in ((start_bottles - take_down + 1)..=start_bottles).rev() {
        let s = num2str(i);
        if i == 1 {
            result.push_str("One green bottle hanging on the wall,\n");
            result.push_str("One green bottle hanging on the wall,\n");
            result.push_str("And if one green bottle should accidentally fall,\n");
            result.push_str("There'll be no green bottles hanging on the wall.\n\n");
        } else {
            push_capitalized(&mut result, s);
            result.push_str(" green bottles hanging on the wall,\n");
            push_capitalized(&mut result, s);
            result.push_str(" green bottles hanging on the wall,\n");
            result.push_str("And if one green bottle should accidentally fall,\n");
            result.push_str("There'll be ");
            result.push_str(num2str(i-1));
            if i-1 == 1 {
                result.push_str(" green bottle hanging on the wall.\n\n");
            } else {
                result.push_str(" green bottles hanging on the wall.\n\n");
            }
        }
    }
    result
}

#[inline(always)]
fn num2str(i: u32) -> &'static str {
    match i {
        1 => "one",
        2 => "two",
        3 => "three",
        4 => "four",
        5 => "five",
        6 => "six",
        7 => "seven",
        8 => "eight",
        9 => "nine",
        10 => "ten",
        _ => "no",
    }
}

#[inline(always)]
fn push_capitalized(to: &mut String, s: &str) {
    let i = to.len();
    to.push_str(s);
    unsafe{
        to.as_bytes_mut()[i] = to.as_bytes_mut()[i] - b'a' + b'A';
    };
}