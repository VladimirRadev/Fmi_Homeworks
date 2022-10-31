use std::io::{self, BufRead};

/*
 * Complete the 'plusMinus' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

fn plusMinus(arr:  &[i32]) {
    let mut posCount:i32 = 0;
    let mut negCount:i32 = 0;
    let mut zeroCount:i32 = 0;
    let mut count=0;

    for elem  in arr{
        if *elem > 0
        {
            posCount+=1;
        }
        else if *elem < 0
        {
            negCount+=1;
        }
        else{
        zeroCount+=1;
        }
        count+=1;
    }

 


    println!("{:.6}",(posCount as f32/count as f32) );
    println!("{:.6}",(negCount as f32 /count as f32) );
    println!("{:.6}",(zeroCount as f32 /count as f32) );

    
}

fn main() {
    let stdin = io::stdin();
    let mut stdin_iterator = stdin.lock().lines();

    let n = stdin_iterator.next().unwrap().unwrap().trim().parse::<i32>().unwrap();

    let arr: Vec<i32> = stdin_iterator.next().unwrap().unwrap()
        .trim_end()
        .split(' ')
        .map(|s| s.to_string().parse::<i32>().unwrap())
        .collect();

    plusMinus(&arr);
}

