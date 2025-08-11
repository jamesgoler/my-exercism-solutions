pub fn annotate(minefield: &[&str]) -> Vec<String> {
    minefield.iter()
             .enumerate()
             .map(|(i, row)| unsafe {
                String::from_utf8_unchecked(
                  row.as_bytes().iter()
                     .enumerate()
                     .map(|(j, &col)| {
                        let mut ch = col;
                        if col == b' ' {
                            let count = count_mine(minefield, i, j);
                            if count > 0 {
                                ch = count + b'0';
                            }
                        }
                        ch
                    })
                    .collect())
              })
             .collect()
}

#[inline(always)]
fn count_mine(m: &[&str], i: usize, j: usize) -> u8 {
    let mut count = count_mine_at_row(m, i, j);
    if i > 0 {
        count += count_mine_at_row(m, i-1, j);
    }
    if i+1 < m.len() {
        count += count_mine_at_row(m, i+1, j);
    }
    count
}

#[inline(always)]
fn count_mine_at_row(m: &[&str], i: usize, j: usize) -> u8 {
    let mut count = count_mine_at_row_col(m, i, j);
    if j > 0 {
        count += count_mine_at_row_col(m, i, j-1);
    }
    if j+1 < m[i].len() {
        count += count_mine_at_row_col(m, i, j+1);
    }
    count
}

#[inline(always)]
fn count_mine_at_row_col(m: &[&str], i: usize, j: usize) -> u8 {
    if m[i].as_bytes()[j] == b'*' {
        1
    } else {
        0
    }
}

