#[derive(Debug, PartialEq, Eq, PartialOrd, Ord)]
pub struct Clock {
    hours: i32,
    minutes: i32,
}

impl std::fmt::Display for Clock {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{:02}:{:02}", self.hours, self.minutes)
    }
}

impl Clock {
    pub fn new(mut hours: i32, mut minutes: i32) -> Self {
        let mut extra_hours = minutes / 60;
        minutes = minutes % 60;
        if minutes < 0 {
            minutes = 60 + minutes;
            extra_hours -= 1;
        }
        // to avoid overflowing, modulo before addition.
        hours = ((hours % 24) + (extra_hours % 24)) % 24;
        if hours < 0 {
            hours += 24;
        }
        Clock { hours, minutes }
    }

    pub fn add_minutes(&self, minutes: i32) -> Self {
        // to avoid integer overflow, turn a minutes into clock first.
        self.add_clock(Clock::new(0, minutes))
    }

    #[inline(always)]
    fn add_clock(&self, other: Clock) -> Self {
        Clock::new(self.hours + other.hours,
                   self.minutes + other.minutes)
    }
}

