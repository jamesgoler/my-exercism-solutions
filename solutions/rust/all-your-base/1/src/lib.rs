#[derive(Debug, PartialEq, Eq)]
pub enum Error {
    InvalidInputBase,
    InvalidOutputBase,
    InvalidDigit(u32),
}

///
/// Convert a number between two bases.
///
/// A number is any slice of digits.
/// A digit is any unsigned integer (e.g. u8, u16, u32, u64, or usize).
/// Bases are specified as unsigned integers.
///
/// Return the corresponding Error enum if the conversion is impossible.
///
///
/// You are allowed to change the function signature as long as all test still pass.
///
///
/// Example:
/// Input
///   number: &[4, 2]
///   from_base: 10
///   to_base: 2
/// Result
///   Ok(vec![1, 0, 1, 0, 1, 0])
///
/// The example corresponds to converting the number 42 from decimal
/// which is equivalent to 101010 in binary.
///
///
/// Notes:
///  * The empty slice ( "[]" ) is equal to the number 0.
///  * Never output leading 0 digits, unless the input number is 0, in which the output must be `[0]`.
///    However, your function must be able to process input with leading 0 digits.
///
pub fn convert(number: &[u32], from_base: u32, to_base: u32) -> Result<Vec<u32>, Error> {
    if !check_base(from_base) {
        return Err(Error::InvalidInputBase);
    }
    if !check_base(to_base) {
        return Err(Error::InvalidOutputBase);
    }

    check_digits(number, from_base)?;

    if number.is_empty() || number.iter().cloned().all(|n| n == 0) {
        return Ok(vec![0]);
    }

    let from_base_in_to_base_lsf = to_base_digits_least_significant_first(from_base, to_base);
    let mut result = vec![];
    let mut term = vec![1];
    for coefficient in number.iter().rev().cloned() {
        let tmp = mul_scaler(&term, coefficient, 0, to_base);
        add_assign(&mut result, &tmp, to_base);
        term = mul(&term, &from_base_in_to_base_lsf, to_base);
    }

    result.reverse();
    Ok(result)
}

fn check_base(base: u32) -> bool {
    base >= 2
}

fn check_digits(number: &[u32], from_base: u32) -> Result<(), Error> {
    for coefficient in number.iter().cloned() {
        if coefficient >= from_base {
            return Err(Error::InvalidDigit(coefficient));
        }
    }
    Ok(())
}

///
/// Convert a decimal number into base `to_base` and
/// store the results in least significant first order.
///
/// Keep the digits in least significant first order for easier processing.
///
fn to_base_digits_least_significant_first(mut number: u32, to_base: u32) -> Vec<u32> {
    let mut result = vec![];

    while number > 0 {
        result.push(number % to_base);
        number /= to_base;
    }

    result
}

fn reserve_digits(number: &mut Vec<u32>, additional: usize) {
    number.reserve(additional);
    for _ in 0..additional {
        number.push(0);
    }
}

fn mul_scaler(a: &[u32], scaler: u32, offset: usize, base: u32) -> Vec<u32> {
    let mut result = vec![];
    reserve_digits(&mut result, offset);

    let mut carry = 0;
    for n in a.iter().cloned() {
        let digit;
        (digit, carry) = carrying_mul_scaler(n, scaler, carry, base);
        result.push(digit);
    }
    if carry > 0 {
        result.push(carry);
    }
    result
}

fn mul(a: &[u32], b: &[u32], base: u32) -> Vec<u32> {
    let mut result = vec![];

    for (offset, scaler) in b.iter().cloned().enumerate() {
        let partial_product = mul_scaler(a, scaler, offset, base);
        add_assign(&mut result, &partial_product, base);
    }

    result
}

fn add_assign(a: &mut Vec<u32>, b: &[u32], base: u32) {
    if b.len() > a.len() {
        reserve_digits(a, b.len() - a.len());
    }

    let mut carry = 0;
    for (i, n) in b.iter().cloned().enumerate() {
        let digit;
        (digit, carry) = carrying_add_scaler(a[i], n, carry, base);
        a[i] = digit;
    }
    if carry > 0 {
        a.push(carry);
    }
}

fn carry_scaler(n: u64, base: u32) -> (u32, u32) {
    ((n % base as u64) as u32, (n / base as u64) as u32)
}

fn carrying_mul_scaler(a: u32, b: u32, carry: u32, base: u32) -> (u32, u32) {
    carry_scaler(a as u64 * b as u64 + carry as u64, base)
}

fn carrying_add_scaler(a: u32, b: u32, carry: u32, base: u32) -> (u32, u32) {
    carry_scaler(a as u64 + b as u64 + carry as u64, base)
}