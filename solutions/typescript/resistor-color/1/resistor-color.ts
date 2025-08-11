const COLORS_MAP = {
  'black': 0,
  'brown': 1,
  'red': 2,
  'orange': 3,
  'yellow': 4,
  'green': 5,
  'blue': 6,
  'violet': 7,
  'grey': 8,
  'white': 9,
};

export const colorCode = (c: keyof typeof COLORS_MAP) => COLORS_MAP[c];
export const COLORS = Object.keys(COLORS_MAP);