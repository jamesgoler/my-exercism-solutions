pub struct Allergies(u32);

#[derive(Debug, PartialEq, Eq, Clone, Copy)]
pub enum Allergen {
    Eggs = 0b0000_0001,
    Peanuts = 0b0000_0010,
    Shellfish = 0b0000_0100,
    Strawberries = 0b0000_1000,
    Tomatoes = 0b0001_0000,
    Chocolate = 0b0010_0000,
    Pollen = 0b0100_0000,
    Cats = 0b1000_0000,
}

impl Allergen {
    const ALL: [Self; 8] = [
        Self::Eggs,
        Self::Peanuts,
        Self::Shellfish,
        Self::Strawberries,
        Self::Tomatoes,
        Self::Chocolate,
        Self::Pollen,
        Self::Cats,
    ];
}

impl Allergies {
    pub fn new(score: u32) -> Self {
        Self(score)
    }

    pub fn is_allergic_to(&self, allergen: &Allergen) -> bool {
        (self.0 & *allergen as u32) != 0
    }

    pub fn allergies(&self) -> Vec<Allergen> {
        Allergen::ALL
            .into_iter()
            .filter(|a| self.is_allergic_to(a))
            .collect()
    }
}
