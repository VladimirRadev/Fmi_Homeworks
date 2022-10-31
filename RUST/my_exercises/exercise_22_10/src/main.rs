use std::io::{self, BufRead};

/*
 * Complete the 'miniMaxSum' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

fn miniMaxSum(arr: &[i32]) {
    let mut min: i64 = 0;
    let mut max: i64 = 0;

    let mut arrVec: Vec<&i32>=arr.iter().collect();

    arrVec.sort();
    let  minRange = &mut  arrVec[..=3].iter();

    while let Some(val) = minRange.next() {
        min+=**val as i64;
    }

    let  maxRange = &mut arrVec[1..].iter();
    while let Some(val) = maxRange.next() {
        max+=**val as i64;
    }

    println!("{} {}",min,max);
}

fn main() {
    let stdin = io::stdin();
    let mut stdin_iterator = stdin.lock().lines();

    let arr: Vec<i32> = stdin_iterator.next().unwrap().unwrap()
        .trim_end()
        .split(' ')
        .map(|s| s.to_string().parse::<i32>().unwrap())
        .collect();

    miniMaxSum(&arr);
}
