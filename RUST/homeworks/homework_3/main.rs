use std::{collections::{HashMap, BTreeMap}, vec, io::Write};
use homework3::*;
use homework3::Interpreter;

fn main(){
    // let stdin = std::io::stdin();
    // let mut stdout = std::io::stdout();
    // stdout.write(format!("{}\n","Value".to_string()).as_bytes());
    // let mut interpreter = Interpreter::new(stdin, &mut stdout);
    // interpreter.add("10 PRINT guess_a_number").unwrap();
    // interpreter.add("20 READ Guess").unwrap();
    // interpreter.add("30 IF Guess > 42 GOTO 100").unwrap();
    // interpreter.add("110 GOTO 10").unwrap();

    // for (key,value) in interpreter.lines  {
    //     println!("{} -> {:?}" , key,value);
    // }

    // let mut interpreter = Interpreter::new(stdin, &mut stdout);
    // interpreter.add("3 PRINT 1").unwrap();
    // interpreter.add("2 PRINT 2").unwrap();
    // interpreter.add("1 PRINT 3").unwrap();
    // interpreter.add("1 PRINT 4").unwrap();

    // for (key,value) in interpreter.lines  {
    //     println!("{} -> {:?}" , key,value);
    // }


    // #lineNum -> ["Command", arguments]
    // let mut example : HashMap<u32,Vec<String>> = HashMap::new();
    // example.insert(10, "PRINT guess_a_number".split_whitespace().map(|x| x.to_string()).collect::<Vec<String>>());

    // let mut  a = "10 PRINT guess_a_number".split_whitespace().map(|x| x.to_string()).collect::<Vec<String>>();
    
    // println!("{:?}",a);
    // println!("{:?}",example.get(&10).unwrap()[1]);

    
    // if 'Щ'.is_uppercase(){
    //     println!("sex")
    // }

    // let mut a = "0астие0".to_string().chars().next().unwrap();
    // if a.is_uppercase(){
    //     println!("sex")
    // }
   

    // for key in example.keys() {
        
    // }

    // let input: &[u8] = b"1\n2\n";
    // let mut output = Vec::<u8>::new();
    // let mut interpreter = Interpreter::new(input, &mut output);

    // interpreter.add("10 READ A").unwrap();
    // interpreter.add("20 READ B").unwrap();
    // interpreter.add("30 PRINT A").unwrap();
    // interpreter.add("40 PRINT B").unwrap();

    // interpreter.vars.insert("X".to_string(), 14);
    // interpreter.run();
    

//    println!("{}",interpreter.eval_value("-1").unwrap());

//    let mut a:BTreeMap<u64,String> = BTreeMap::new();
//     a.insert(10, "print".to_string());
//     a.insert(30, "if".to_string());

//     a.insert(20, "goto".to_string());
//     let mut b= a.get(&20);
//     println!("{:?}" ,b)
    // for  (key,value)   in &a {
    //     println!("{} {} ", key,value);
    // }

    // let mut a:Vec<u16>=Vec::new();
    // a.push(1);
    // a.push(0);
    // a.sort();
    // a[1];


    let stdin = std::io::stdin();
    let mut stdout = std::io::stdout();
    let mut interpreter = Interpreter::new(stdin, &mut stdout);

    interpreter.add("10 PRINT guess_a_number").unwrap();
    // interpreter.add("13 PRINT guess").unwrap();
    // interpreter.add("15 PRINT guess").unwrap();
    // interpreter.add("20 READ Guess").unwrap();
    // interpreter.add("21 IF Gess < 1 GOTO 13 ").unwrap();

    // println!("{}", interpreter.eval_value("x").unwrap());

    interpreter.add("20 READ Guess").unwrap();
    interpreter.add("30 IF Guess > 4 GOTO 100").unwrap();
    interpreter.add("40 IF Guess < 4 GOTO 200").unwrap();
    interpreter.add("50 IF Guess = 4 GOTO 300").unwrap();

    interpreter.add("100 PRINT too_high").unwrap();

    interpreter.add("110 GOTO 10").unwrap();

    interpreter.add("200 PRINT too_low").unwrap();
    interpreter.add("300 PRINT you_got_it!").unwrap();

    interpreter.add("210 GOTO 10").unwrap();



    
   interpreter.run().unwrap();


  //  let input = NotBuffered {};
  //  let mut output = std::io::stdout();
    //let mut interpreter = Interpreter::new(input, &mut output);

   // interpreter.add("10 PRINT 10").unwrap();
    //interpreter.run().unwrap();
    

    



   

    
}