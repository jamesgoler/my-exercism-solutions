#[derive(Debug)]
pub struct HighScores<'a>(&'a [u32]);

impl <'a> HighScores<'a> {
    pub fn new(scores: &'a [u32]) -> Self {
        Self(scores)
    }

    pub fn scores(&self) -> &[u32] {
        self.0
    }

    pub fn latest(&self) -> Option<u32> {
        self.0.last().copied()
    }

    pub fn personal_best(&self) -> Option<u32> {
        self.0.iter().max().copied()
    }

    pub fn personal_top_three(&self) -> Vec<u32> {
        let mut result = vec![];
        for &n in self.0.iter() {
            if result.len() < 3 {
                result.push(n);
            } else if n < result[2] {
                continue;
            }
            let mut i = result.len()-1;
            while i > 0 && n > result[i-1] {
                result[i] = result[i-1];
                i -= 1;
            }
            result[i] = n;
        }
        result
    }
}
