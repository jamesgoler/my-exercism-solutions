const COLOR_MAP = {
    "black": 0,
    "brown": 1,
    "red": 2,
    "orange": 3,
    "yellow": 4,
    "green": 5,
    "blue": 6,
    "violet": 7,
    "grey": 8,
    "white": 9,
};

export function decodedValue(resistors: Array<keyof typeof COLOR_MAP>) {
  return COLOR_MAP[resistors[0]] * 10 + COLOR_MAP[resistors[1]];
}
