
#[derive(Debug, PartialEq, PartialOrd, Clone)]
struct Num([u8; 6]);

impl Num {
    fn from_i32(input: i32) -> Self {
        let d0 = ((input / 100_000) % 10) as u8;
        let d1 = ((input / 10_000) % 10) as u8;
        let d2 = ((input / 1_000) % 10) as u8;
        let d3 = ((input / 100) % 10) as u8;
        let d4 = ((input / 10) % 10) as u8;
        let d5 = (input % 10) as u8;

        Self {
            0: [d0, d1, d2, d3, d4, d5],
        }
    }

    fn inc(&mut self) {
        for i in (0..6).into_iter().rev() {
            self.0[i] += 1;
            if self.0[i] != 10 {
                return;
            }

            if i == 0 {
                self.0[i] = 0;
            } else {
                self.0[i] = self.0[i - 1];
            }
        }
    }
}


fn main() {
    // let start = 347312;
    // let end = 805915;
    let start = 136818;
    let end = 685979;

    let mut hit_counter1: i32 = 0;
    for n in start .. end+1 {
        if never_decreases(&n) && has_at_least_two_adjacent_digits(&n) {
            hit_counter1 += 1;
        }
    }

    let mut hit_counter2: i32 = 0;
    for n in start .. end+1 {
        if never_decreases(&n) && has_two_adjacent_digits(&n) {
            hit_counter2 += 1;
        }
    }
    println!("Part 1: {} hits in range {}-{}", hit_counter1, start, end);
    println!("Part 2: {} hits in range {}-{}", hit_counter2, start, end);
}

fn has_at_least_two_adjacent_digits(n: &i32) -> bool {
    let as_string = n.to_string();
    let digit_list = as_string.char_indices();

    let mut last_digit: char = '0';

    for (i, digit) in digit_list {
        if i == 0 {
            last_digit = digit;
            continue;
        }

        if digit == last_digit {
            return true;
        }

        last_digit = digit;
    }

    return false;
}

// https://gist.github.com/vlmonk/8f466c8b2d99c4bc0be3b355b783c44a
fn is_2_digit_same_advanced(n: &i32) -> bool {
    let input = Num::from_i32(*n);

    let input = input.0;

    (0..5).any(|i| match i {
        0 => (input[0] == input[1]) && (input[0] != input[2]),
        4 => (input[4] == input[5]) && (input[4] != input[3]),
        n => (input[n] == input[n + 1]) && (input[n] != input[n - 1]) && (input[n] != input[n + 2]),
    })
}


fn has_two_adjacent_digits(n: &i32) -> bool {
    let as_string = n.to_string();
    let digit_list = as_string.char_indices();

    let mut last_digit: char = '0';
    let mut last_pair: bool = false;
    let mut has_passed: bool = false;

    // [1, 2, 2, 3, 3, 3]
    // [false, false, true, false, true, true]

    for (i, digit) in digit_list {
        if i == 0 {
            last_digit = digit;
            continue;
        }

        let current_pair = digit == last_digit;
        if !current_pair {
            if has_passed {
                break;
            }

            // they aren't matching, falses don't affect outcome
            last_pair = current_pair;
            last_digit = digit;
            continue;
        }

        // they must be matching
        if !has_passed {
            if !last_pair {
                // no pair before this and we haven't passed. now we have
                has_passed = true;
            }
        } else {
            if last_pair {
                // the last one was a pair, which means this is the same number
                // fail for now
                has_passed = false;
            }
        }

        last_pair = current_pair;
        last_digit = digit;
    }

    return has_passed;
}

fn never_decreases(n: &i32) -> bool {
    let as_string = n.to_string();
    let digit_list = as_string.chars();

    let mut last_digit: char = '0';

    for digit in digit_list {
        if digit < last_digit {
            return false;
        }

        last_digit = digit;
    }

    return true;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_has_at_least_two_adjacent_digits() {
        struct Case {
            n: i32,
            output: bool,
        }

        let cases = vec![
            Case {
                n: 444444,
                output: true,
            },
            Case {
                n: 123456,
                output: false
            },
            Case {
                n: 122345,
                output: true
            },
            Case {
                n: 123452,
                output: false
            },
        ];

        for case in cases.iter() {
            let res = has_at_least_two_adjacent_digits(&case.n);

            assert_eq!(case.output, res, "{}", case.n);
        }
    }

    #[test]
    fn test_has_two_adjacent_digits() {
        struct Case {
            n: i32,
            output: bool,
        }

        let cases = vec![
            Case {
                n: 444444,
                output: false,
            },
            Case {
                n: 111122,
                output: true,
            },
            Case {
                n: 123456,
                output: false
            },
            Case {
                n: 122345,
                output: true
            },
            Case {
                n: 123452,
                output: false
            },
            Case {
                n: 123444,
                output: false
            },
            Case {
                n: 222445,
                output: true
            },
            Case {
                n: 112233,
                output: true
            },
            Case {
                n: 112699,
                output: true
            },
            Case {
                n: 112689,
                output: true
            },
            Case {
                n: 112189,
                output: true
            },
            Case {
                n: 122333,
                output: true
            },
            Case {
                n: 122334,
                output: true
            },
            Case {
                n: 122334,
                output: true
            },
            Case {
                n: 222345,
                output: false
            },
            Case {
                n: 123455,
                output: true
            },
            Case {
                n: 133455,
                output: true
            },
            Case {
                n: 333455,
                output: true
            },
            Case {
                n: 333345,
                output: false
            },
        ];

        for case in cases.iter() {
            // let res = is_2_digit_same_advanced(&case.n);
            let res = has_two_adjacent_digits(&case.n);

            assert_eq!(case.output, res, "{}", case.n);
        }
    }

    #[test]
    fn test_never_decreases() {
        struct Case {
            n: i32,
            output: bool,
        }

        let cases = vec![
            Case {
                n: 444444,
                output: true,
            },
            Case {
                n: 123456,
                output: true
            },
            Case {
                n: 122645,
                output: false
            },
            Case {
                n: 123452,
                output: false
            },
        ];

        for case in cases.iter() {
            let res = never_decreases(&case.n);

            assert_eq!(case.output, res, "{}", case.n);
        }
    }
}
