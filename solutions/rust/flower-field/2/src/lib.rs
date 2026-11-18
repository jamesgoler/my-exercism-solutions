pub fn annotate(garden: &[&str]) -> Vec<String> {
    if garden.is_empty() {
        return vec![];
    }

    let mut result = vec![String::with_capacity(garden[0].len()); garden.len()];
    for i in 0..garden.len() {
        for j in 0..garden[i].len() {
            result[i].push(get_annotation_char(garden, i, j));
        }
    }

    result
}

fn get_annotation_char(garden: &[&str], i: usize, j: usize) -> char {
    if is_flower(garden, i, j) {
        return '*';
    }
    let count = count_surrounding_flowers(garden, i, j);
    if count == 0 {
        ' '
    } else {
        (b'0' + count) as char
    }
}

fn count_surrounding_flowers(garden: &[&str], i: usize, j: usize) -> u8 {
    const DIRECTIONS: [(isize, isize); 8] = [
        (-1, -1),
        (-1, 0),
        (-1, 1),
        (0, -1),
        (0, 1),
        (1, -1),
        (1, 0),
        (1, 1),
    ];

    DIRECTIONS
        .iter()
        .filter_map(|dir| {
            let x = i.checked_add_signed(dir.0)?;
            let y = j.checked_add_signed(dir.1)?;
            if x >= garden.len() || y >= garden[x].len() {
                None
            } else {
                Some((x, y))
            }
        })
        .filter(|&(x, y)| is_flower(garden, x, y))
        .count() as u8
}

fn is_flower(garden: &[&str], i: usize, j: usize) -> bool {
    garden[i].as_bytes()[j] == b'*'
}