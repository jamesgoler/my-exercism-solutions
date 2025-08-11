pub fn is_armstrong_number(num: u32) -> bool {
    let pow = num.checked_ilog10().unwrap_or(0) + 1;
    let mut power_sum = 0;
    let mut tmp = num;
    while tmp > 0 {
        power_sum += (tmp % 10).pow(pow);
        tmp /= 10;
    }
    power_sum == num
}
