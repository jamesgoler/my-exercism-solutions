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

const UNITS = ['ohms', 'kiloohms', 'megaohms', 'gigaohms'];

export function decodedResistorValue(bands: (keyof typeof COLOR_MAP)[]): string {
  let value = COLOR_MAP[bands[0]] * 10 + COLOR_MAP[bands[1]];
  let pow = COLOR_MAP[bands[2]];
  if (value === 0) {
    pow = 0;
  } else if (value % 10 === 0) {
    pow += 1;
    value /= 10;
  }
  let unit = Math.floor(pow / 3);
  value *= Math.pow(10, (pow % 3));
  return `${value} ${UNITS[unit]}`;
}
