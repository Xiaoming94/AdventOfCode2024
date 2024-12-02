type Report = Vec<u32>;

enum ReportSafety {
    Unsafe,
    Safe(Report),
}

pub(crate) fn find_safe_reports(input: &str) -> u32 {
    println!("this is the input\n{input}");
    42
}
