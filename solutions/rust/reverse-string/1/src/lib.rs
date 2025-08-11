pub fn reverse(input: &str) -> String {
    let input = input.as_bytes();
    let mut buf = Vec::with_capacity(input.len());
    
    // Iterate over every UTF-8 char begining.
    let mut last = input.len();
    for (i, &b) in input.iter()
                        .enumerate()
                        .filter(|&(_, &b)| (b & 0b1100_0000) != 0b1000_0000)
                        .rev()
    {
        buf.extend_from_slice(&input[i..last]);
        last = i;
    }
    unsafe { String::from_utf8_unchecked(buf) }
}
