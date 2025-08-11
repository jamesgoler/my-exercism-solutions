pub fn plants(diagram: &str, student: &str) -> Vec<&'static str> {
    let i = ((student.as_bytes()[0] - b'A') as usize) << 1;
    let j = diagram.find('\n').unwrap() + 1 + i;
    
    let bytes = diagram.as_bytes();
    vec![
        code_to_plant(bytes[i]),
        code_to_plant(bytes[i + 1]),
        code_to_plant(bytes[j]),
        code_to_plant(bytes[j + 1]),
    ]
}


fn code_to_plant(code: u8) -> &'static str {
    match code {
        b'G' => "grass",
        b'C' => "clover",
        b'R' => "radishes",
        b'V' => "violets",
        _ => panic!("decode error!"),
    }
}