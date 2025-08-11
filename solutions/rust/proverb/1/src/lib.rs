pub fn build_proverb(list: &[&str]) -> String {
    if list.is_empty() {
        return String::new();
    }
    let mut expect_len = ((list.iter().map(|l| l.len()).sum::<usize>() * 2) - list[list.len()-1].len()) +
                         list.len() * "For want of a  the  was lost.\n".len() +
                         "And all for the want of a .".len();

    let mut result = String::with_capacity(expect_len);

    for l in list.windows(2) {
        result.push_str("For want of a ");
        result.push_str(l[0]);
        result.push_str(" the ");
        result.push_str(l[1]);
        result.push_str(" was lost.\n");
    }
    result.push_str("And all for the want of a ");
    result.push_str(list[0]);           
    result.push_str(".");
    result
}

