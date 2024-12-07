mod solution;

use inputreader;

fn main() {
    let input = inputreader::read_input();
    println!("The input is :\n{}", input);
    println!(
        "Solution for problem1: {}",
        solution::find_valid_equations(input.as_str())
    );

    println!(
        "Solution for problem2: {}",
        solution::find_valid_equations_concat(input.as_str())
    );
}

#[cfg(test)]
mod tests {
    use super::solution;
    use googletest::prelude::*;
    const INPUT: &str = "190: 10 19\n\
                        3267: 81 40 27\n\
                        83: 17 5\n\
                        156: 15 6\n\
                        7290: 6 8 6 15\n\
                        161011: 16 10 13\n\
                        192: 17 8 14\n\
                        21037: 9 7 18 13\n\
                        292: 11 6 16 20";

    #[test]
    fn verify_problem1solution() {
        let results = solution::find_valid_equations(INPUT);
        assert_that!(results, eq(3749));
    }

    #[test]
    fn verify_problem2solution() {
        let results = solution::find_valid_equations_concat(INPUT);
        assert_that!(results, eq(11387));
    }
}
