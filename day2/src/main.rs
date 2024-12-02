mod solutions;

use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let input = stdin
        .lock()
        .lines()
        .fold("".to_string(), move |input, line| {
            input + line.unwrap().as_str() + "\n"
        });
    println!("input is: {input}");
    println!(
        "Result problem1: {}",
        solutions::find_safe_reports(input.as_str())
    );

    println!(
        "Result problem2: {}",
        solutions::find_safe_reports_with_dampener(input.as_str())
    );
}

#[cfg(test)]
mod day2tests {
    use crate::solutions;
    use googletest::prelude::*;
    const INPUT: &str = "7 6 4 2 1\n\
                         1 2 7 8 9\n\
                         9 7 6 2 1\n\
                         1 3 2 4 5\n\
                         8 6 4 4 1\n\
                         1 3 6 7 9";
    #[gtest]
    fn verify_problem1solution() {
        let result = solutions::find_safe_reports(INPUT);
        assert_that!(result, eq(2));
    }

    #[test]
    fn verify_problem2solution() {
        let result = solutions::find_safe_reports_with_dampener(INPUT);
        assert_that!(result, eq(4));
    }
}
