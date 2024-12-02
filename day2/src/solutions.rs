type Report = Vec<i32>;

enum ReportSafety {
    Unsafe,
    Safe(Report),
}

impl ReportSafety {
    fn is_safe(&self) -> bool {
        use ReportSafety::*;
        if let Safe(_) = *self {
            true
        } else {
            false
        }
    }
}

fn create_report(report_line: &str) -> Report {
    report_line
        .split_whitespace()
        .map(|number| {
            number
                .parse::<i32>()
                .unwrap_or_else(|input| panic!("Cannot parse: {:?}", input))
        })
        .collect()
}

fn check_safety(report: Report) -> ReportSafety {
    fn test_is_ascending(report: &Report) -> (bool, &i32) {
        if let Some(first) = report.get(0) {
            if let Some(second) = report.get(1) {
                (first < second, first)
            } else {
                panic!("invalid input");
            }
        } else {
            panic!("invalid input");
        }
    }

    let (is_ascending, mut elem) = test_is_ascending(&report);

    fn unacceptable_diff(first: i32, second: i32) -> bool {
        let diff = (first - second).abs();
        diff < 1 || diff > 3
    }
    for num in &report[1..] {
        if (unacceptable_diff(*num, *elem) || is_ascending && num < elem)
            || (!is_ascending && num > elem)
        {
            println!("report: {:?} is Unsafe", report);
            return ReportSafety::Unsafe;
        }

        elem = num
    }

    println!("report: {:?} is Safe", report);

    return ReportSafety::Safe(report);
}

pub(crate) fn find_safe_reports(input: &str) -> u32 {
    input
        .lines()
        .map(create_report)
        .map(check_safety)
        .filter(|report| report.is_safe())
        .count() as u32
}
