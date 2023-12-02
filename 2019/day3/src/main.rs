// https://adventofcode.com/2019/day/3

use bit_vec::BitVec;
use std::collections::HashMap;
use std::fs;
use std::io::Error;

#[derive(Copy, Clone)]
#[derive(Hash)]
struct Point {
    x: i32,
    y: i32,
}

impl PartialEq for Point {
    fn eq(&self, other: &Self) -> bool {
        self.x == other.x && self.y == other.y
    }
}

impl Eq for Point {}

fn main() -> Result<(), Error> {
    let data = match fs::read_to_string("./data.txt") {
        Ok(data) => data,
        Err(e) => return Err(e),
    };
    let wires: Vec<&str> = data.trim().split("\n").collect();
    let wire1: Vec<&str> = wires[0].split(",").collect();
    let wire2: Vec<&str> = wires[1].split(",").collect();

    let manhattan_distance = get_best_manhattan_distance(&wire1, &wire2);
    println!("part 1 | manhattan distance: {}", manhattan_distance);

    let fewest_steps = get_fewest_steps(&wire1, &wire2);
    println!("part 2 | fewest steps: {}", fewest_steps);

    Ok(())
}

fn get_best_manhattan_distance(wire1: &Vec<&str>, wire2: &Vec<&str>) -> i32 {
    let mut board: HashMap<Point, BitVec> = HashMap::new();

    let mut current_position = Point {
        x: 0,
        y: 0,
    };

    for instr in wire1.iter() {
        if instr.len() == 0 {
            break;
        };
        let direction: char = instr.chars().next().unwrap();
        let distance: i32 = instr[1..].parse().unwrap();

        let mut n = 1;
        while n <= distance {
            if direction == 'U' {
                current_position.y += 1;
            } else if direction == 'D' {
                current_position.y -= 1;
            } else if direction == 'L' {
                current_position.x -= 1;
            } else if direction == 'R' {
                current_position.x += 1;
            }

            // may be an old point or a new one
            let pos = board.entry(current_position).or_insert(BitVec::from_elem(2, false));
            // set it to be sure
            pos.set(0, true);

            n += 1;
        }
    }

    // reinitialize the current position
    current_position.x = 0;
    current_position.y = 0;

    for instr in wire2.iter() {
        if instr.len() == 0 {
            break;
        };
        let direction: char = instr.chars().next().unwrap();
        let distance: i32 = instr[1..].parse().unwrap();

        let mut n = 1;
        while n <= distance {
            if direction == 'U' {
                current_position.y += 1;
            } else if direction == 'D' {
                current_position.y -= 1;
            } else if direction == 'L' {
                current_position.x -= 1;
            } else if direction == 'R' {
                current_position.x += 1;
            }

            // may be an old point or a new one
            let pos = board.entry(current_position).or_insert(BitVec::from_elem(2, false));
            // set it to be sure
            pos.set(1, true);

            n += 1;
        }
    }

    let mut best_crossing = Point {
        x: 100000,
        y: 100000,
    };

    for (position, bv) in board {
        if bv[0] && bv[1] {
            let new_manhattan_distance = position.x.abs() + position.y.abs();
            let old_manhattan_distance = best_crossing.x.abs() + best_crossing.y.abs();

            if new_manhattan_distance < old_manhattan_distance {
                best_crossing = position
            }
        }
    }

    return best_crossing.x.abs() + best_crossing.y.abs();
}

#[derive(Copy, Clone)]
#[derive(Hash)]
struct Steps {
    wire1: i32,
    wire2: i32,
}

fn get_fewest_steps(wire1: &Vec<&str>, wire2: &Vec<&str>) -> i32 {
    let mut board: HashMap<Point, Steps> = HashMap::new();

    let mut current_position = Point {
        x: 0,
        y: 0,
    };

    let mut steps_so_far = 0;

    for instr in wire1.iter() {
        if instr.len() == 0 {
            break;
        };
        let direction: char = instr.chars().next().unwrap();
        let distance: i32 = instr[1..].parse().unwrap();

        let mut n = 1;
        while n <= distance {
            steps_so_far += 1;

            if direction == 'U' {
                current_position.y += 1;
            } else if direction == 'D' {
                current_position.y -= 1;
            } else if direction == 'L' {
                current_position.x -= 1;
            } else if direction == 'R' {
                current_position.x += 1;
            }

            // we only need to insert new positions. if one already exists, it was lower
            board.entry(current_position).or_insert(Steps {wire1: steps_so_far, wire2: 0,});

            n += 1;
        }
    }

    current_position.x = 0;
    current_position.y = 0;
    steps_so_far = 0;

    for instr in wire2.iter() {
        if instr.len() == 0 {
            break;
        };
        let direction: char = instr.chars().next().unwrap();
        let distance: i32 = instr[1..].parse().unwrap();

        let mut n = 1;
        while n <= distance {
            steps_so_far += 1;

            if direction == 'U' {
                current_position.y += 1;
            } else if direction == 'D' {
                current_position.y -= 1;
            } else if direction == 'L' {
                current_position.x -= 1;
            } else if direction == 'R' {
                current_position.x += 1;
            }

            // we only need to worry about existing positions
            if let Some(pos) = board.get_mut(&current_position) {
                pos.wire2 = steps_so_far;
            }

            n += 1;
        }
    }

    let mut best_so_far = 100000;

    for (_position, steps) in board {
        if steps.wire1 > 0 && steps.wire2 > 0 && steps.wire1 + steps.wire2 < best_so_far {
            best_so_far = steps.wire1 + steps.wire2;
        }
    }

    return best_so_far;
}

#[cfg(test)]
mod tests {
    use super::*;

    struct Case<'a> {
        wire1: Vec<&'a str>,
        wire2: Vec<&'a str>,
        out: i32,
    }

    #[test]
    fn test_best_manhattan_distance() {
        let cases = vec![
            Case {
                wire1: vec!["R75", "D30", "R83", "U83", "L12", "D49", "R71", "U7", "L72"],
                wire2: vec!["U62", "R66", "U55", "R34", "D71", "R55", "D58", "R83"],
                out: 159,
            },
            Case {
                wire1: vec!["R98", "U47", "R26", "D63", "R33", "U87", "L62", "D20", "R33", "U53", "R51"],
                wire2: vec!["U98", "R91", "D20", "R16", "D67", "R40", "U7", "R15", "U6", "R7"],
                out: 135
            },
        ];

        for case in cases.iter() {
            let res = get_best_manhattan_distance(&case.wire1, &case.wire2);
            assert_eq!(case.out, res);
        }
    }

    #[test]
    fn test_fewest_steps() {
        let cases = vec![
            Case {
                wire1: vec!["R75", "D30", "R83", "U83", "L12", "D49", "R71", "U7", "L72"],
                wire2: vec!["U62", "R66", "U55", "R34", "D71", "R55", "D58", "R83"],
                out: 610,
            },
            Case {
                wire1: vec!["R98", "U47", "R26", "D63", "R33", "U87", "L62", "D20", "R33", "U53", "R51"],
                wire2: vec!["U98", "R91", "D20", "R16", "D67", "R40", "U7", "R15", "U6", "R7"],
                out: 410
            },
        ];

        for case in cases.iter() {
            let res = get_fewest_steps(&case.wire1, &case.wire2);
            assert_eq!(case.out, res);
        }
    }
}
