use std::io::{self, BufRead};

pub fn read_input() -> String {
    let stdin = io::stdin();
    let input = stdin
        .lock()
        .lines()
        .fold("".to_string(), move |input, line| {
            input + line.unwrap().as_str() + "\n"
        });
    input
}
