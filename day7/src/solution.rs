type Equation = (u32, Vec<u32>);

enum Results {
    Valid,
    Invalid,
}

fn create_equation(line: &str) -> Equation {
    if let Some((lhs, rhs)) = line.split_once(':') {
        let lhs_out: u32 = lhs.parse().unwrap();
        let operands: Vec<u32> = rhs
            .split_whitespace()
            .map(|num| num.parse::<u32>().unwrap())
            .collect();

        return (lhs_out, operands);
    } else {
        panic!("invalid equation line detected");
    }
}

pub(crate) fn find_valid_equations(input: &str) -> u32 {
    let equations: Vec<Equation> = input.lines().map(create_equation).collect();

    0
}
