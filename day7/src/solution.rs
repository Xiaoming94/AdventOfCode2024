use std::collections::VecDeque;

type RhsType = u64;
type Operands = VecDeque<RhsType>;
type Equation = (RhsType, Operands);

#[derive(Clone, Copy, Debug, Eq, PartialEq)]
enum Evaluation {
    Valid,
    Invalid,
}

fn create_equation(line: &str) -> Equation {
    if let Some((lhs, rhs)) = line.split_once(':') {
        let lhs_out: RhsType = lhs.parse().unwrap();
        let operands: Operands = rhs
            .split_whitespace()
            .map(|num| num.parse::<RhsType>().unwrap())
            .collect();

        return (lhs_out, operands);
    } else {
        panic!("invalid equation line detected");
    }
}

fn concat_nums(lhs: RhsType, mut rhs: RhsType) -> RhsType {
    let mut rhs_vec = Vec::new();

    while rhs != 0 {
        rhs_vec.push(rhs % 10);
        rhs = rhs / 10;
    }

    rhs_vec
        .into_iter()
        .rev()
        .fold(lhs, move |lhs, val| lhs * 10 + val)
}
fn try_evaluate_(
    lhs: RhsType,
    current_val: RhsType,
    mut operands: Operands,
    use_concat: bool,
) -> Evaluation {
    if operands.is_empty() {
        return if current_val == lhs {
            Evaluation::Valid
        } else {
            Evaluation::Invalid
        };
    }

    let operand = operands.pop_front().unwrap();
    if lhs == current_val + operand || lhs == current_val * operand {
        return Evaluation::Valid;
    }

    if use_concat && lhs == concat_nums(current_val, operand) {
        return Evaluation::Valid;
    }

    if try_evaluate_(lhs, current_val * operand, operands.clone(), use_concat)
        == Evaluation::Invalid
    {
        if use_concat
            && try_evaluate_(
                lhs,
                concat_nums(current_val, operand),
                operands.clone(),
                use_concat,
            ) == Evaluation::Valid
        {
            return Evaluation::Valid;
        }
        try_evaluate_(lhs, current_val + operand, operands.clone(), use_concat)
    } else {
        Evaluation::Valid
    }
}

fn try_evaluate(expression: Equation) -> Evaluation {
    let (lhs, mut rhs_ops) = expression;

    let first_op = rhs_ops.pop_front().expect("getting first operand");
    return try_evaluate_(lhs, first_op, rhs_ops.clone(), false);
}

fn try_evaluate_with_concat(expression: Equation) -> Evaluation {
    let (lhs, mut rhs_ops) = expression;

    let first_op = rhs_ops.pop_front().expect("getting first operand");
    return try_evaluate_(lhs, first_op, rhs_ops.clone(), true);
}

pub(crate) fn find_valid_equations(input: &str) -> RhsType {
    let equations: Vec<Equation> = input.lines().map(create_equation).collect();

    equations
        .into_iter()
        .filter(|expression| {
            let result = try_evaluate(expression.clone());
            result == Evaluation::Valid
        })
        .fold(0, move |acc, (lhs, _)| acc + lhs)
}

pub(crate) fn find_valid_equations_concat(input: &str) -> RhsType {
    let equations: Vec<Equation> = input.lines().map(create_equation).collect();

    equations
        .into_iter()
        .filter(|expression| {
            let result = try_evaluate_with_concat(expression.clone());
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

    #[gtest]
    fn test_concat() {
        expect_eq!(56, concat_nums(5, 6));
    }

    #[gtest]
    fn test_concat_big_numbers() {
        expect_eq!(2378, concat_nums(23, 78));
    }
}
