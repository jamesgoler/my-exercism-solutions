use std::collections::HashMap;

#[derive(Debug, PartialEq, Eq)]
pub enum Comparison {
    Equal,
    Sublist,
    Superlist,
    Unequal,
}


pub fn sublist(first_list: &[i32], second_list: &[i32]) -> Comparison {
    if first_list == second_list {
        Comparison::Equal
    } else if first_list.len() > second_list.len() && boyer_moore(first_list, second_list) {
        Comparison::Superlist
    } else if first_list.len() < second_list.len() && boyer_moore(second_list, first_list) {
        Comparison::Sublist
    } else {
        Comparison::Unequal
    }
}

#[inline(always)]
fn boyer_moore(src: &[i32], pat: &[i32]) -> bool {
    if pat.is_empty() {
        return true;
    }
    
    let mut bads = HashMap::new();
    for (i, &p) in pat[..pat.len()-1].iter().enumerate() {
        bads.insert(p, pat.len() - 1 - i);
    }

    let mut i = 0;
    while i + pat.len() <= src.len() {
        if let Some(j) = find_mismatch(&src[i..i+pat.len()], pat) {
            i += *bads.get(&src[i+j]).unwrap_or(&pat.len());
        } else {
            return true;
        }
    }
    false
}

#[inline(always)]
fn find_mismatch(a: &[i32], b: &[i32]) -> Option<usize> {
    for (i, (&a, &b)) in a.iter().zip(b.iter()).enumerate().rev() {    
        if a != b {
            return Some(i);
        }
    }
    None
}