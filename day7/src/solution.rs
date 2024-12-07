use std::collections::VecDeque;

type Operands = VecDeque<u32>;
type Equation = (u32, Operands);

#[derive(Clone, Copy, Debug, Eq, PartialEq)]
enum Evaluation {
    Valid,
    Invalid,
}

fn create_equation(line: &str) -> Equation {
    if let Some((lhs, rhs)) = line.split_once(':') {
        let lhs_out: u32 = lhs.parse().unwrap();
        let operands: VecDeque<u32> = rhs
            .split_whitespace()
            .map(|num| num.parse::<u32>().unwrap())
            .collect();

        return (lhs_out, operands);
    } else {
        panic!("invalid equation line detected");
    }
}

fn try_evaluate(expression: Equation) -> Evaluation {
    let (lhs, mut rhs_ops) = expression;
    fn try_evaluate_(lhs: u32, current_val: u32, mut operands: Operands) -> Evaluation {
        if operands.is_empty() {
            return if current_val == lhs {
                Evaluation::Valid
            } else {
                Evaluation::Invalid
            };
        }

        let operand = operands.pop_front().unwrap();
        if lhs == current_val + operand || lhs == current_val * operand {
            Evaluation::Valid
        } else if try_evaluate_(lhs, current_val * operand, operands.clone()) == Evaluation::Invalid
        {
            try_evaluate_(lhs, current_val + operand, operands.clone())
        } else {
            Evaluation::Valid
        }
    }

    let first_op = rhs_ops.pop_front().expect("getting first operand");
    return try_evaluate_(lhs, first_op, rhs_ops.clone());
}

pub(crate) fn find_valid_equations(input: &str) -> u32 {
    let equations: Vec<Equation> = input.lines().map(create_equation).collect();

    equations
        .into_iter()
        .filter(|expression| {
            let result = try_evaluate(expression.clone());
            result == Evaluation::Valid
        })
        .fold(0, move |acc, (lhs, _)| acc + lhs)
}

#[cfg(test)]
mod tests {
    use super::*;

    use googletest::prelude::*;

    #[gtest]
    fn test_valid_equations() {
        let input = "12: 3 4";
        let expected_result = (12, VecDeque::from([3, 4]));
        expect_eq!(create_equation(input), expected_result)
    }

    #[test]
    #[should_panic]
    fn test_invalid_equation() {
        create_equation("asd");
    }

    #[gtest]
    fn test_evaluating_expression() {
        let equation: Equation = (12, VecDeque::from([3, 4]));
        expect_eq!(Evaluation::Valid, try_evaluate(equation));
    }
}
