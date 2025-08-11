pub fn egg_count(mut display_value: u32) -> usize {
    let mut res = 0;
    while display_value > 0 {
        if display_value & 1 == 1 {
            res += 1;
        }
        display_value >>= 1;
    }
    res
}
