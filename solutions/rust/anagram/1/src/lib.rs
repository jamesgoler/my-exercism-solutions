use std::collections::HashSet;
use std::collections::HashMap;

pub fn anagrams_for<'a>(word: &str, possible_anagrams: &[&'a str]) -> HashSet<&'a str> {
    let mut result = HashSet::new();
    let lower_word = word.to_lowercase();
    let counts_word = count_chars(&lower_word);
    for &pa in possible_anagrams.iter() {
        let lower_pa = pa.to_lowercase();
        if lower_word != lower_pa {
            if counts_word == count_chars(&lower_pa) {
                result.insert(pa);
            }
        }
    }
    result
}

fn count_chars(word: &str) -> HashMap<char, usize> {
    let mut counts = HashMap::with_capacity(word.len());
    for ch in word.chars() {
        *counts.entry(ch).or_insert(0) += 1;
    }
    counts
}
