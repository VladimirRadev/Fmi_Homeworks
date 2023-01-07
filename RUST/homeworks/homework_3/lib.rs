use std::{
    collections::{HashMap},
    io::{self, BufReader, Read, Write, BufRead}
};

#[derive(Debug)]
pub enum InterpreterError {
    IoError(io::Error),
    UnknownVariable { name: String },
    NotANumber { value: String },
    SyntaxError { code: String },
    RuntimeError { line_number: u16, message: String },
}

// ВАЖНО: тук ще трябва да се добави lifetime анотация!
pub struct Interpreter<'a, R: Read, W: Write> {
    // Тези полета не са публични, така че може да си ги промените, ако искате:
    pub output: &'a mut W,
    pub reader: BufReader<R>,
    pub  lines: HashMap<u16, Vec<String>>, // Каквито други полета ви трябват
    pub  vars: HashMap<String,u16>
}

impl<'a, R: Read, W: Write> Interpreter<'a, R, W> {
    /// Конструира нов интерпретатор, който чете вход от `input` чрез `READ` командата и пише в
    /// `output` чрез `PRINT`.
    ///
    pub fn new(input: R, output: &'a mut W) -> Self {
        Self {
            output: output,
            reader: BufReader::new(input),
            lines: HashMap::new(),
            vars : HashMap::new()
        }
    }
}

// Не забравяйте lifetime анотацията
impl<'a, R: Read, W: Write> Interpreter<'a, R, W> {
    /// Тази функция добавя ред код към интерпретатора. Този ред се очаква да започва с 16-битово
    /// unsigned число, последвано от някаква команда и нейните параметри. Всички компоненти на
    /// реда ще бъдат разделени точно с един интервал -- или поне така ще ги тестваме.
    ///
    /// Примерни редове:
    ///
    /// 10 IF 2 > 1 GOTO 30
    /// 20 GOTO 10
    /// 30 READ V
    /// 40 PRINT V
    ///
    /// В случай, че реда не е валидна команда (детайли по-долу), очакваме да върнете
    /// `InterpreterError::SyntaxError` с кода, който е бил подаден.
    ///
    pub fn add(&mut self, code: &str) -> Result<(), InterpreterError> {
        if code.is_empty() {
            return Err(InterpreterError::SyntaxError {
                code: code.to_string(),
            });
        }
        
        // line {
        // 0      1          2          3        4        5           6
        // 10     IF      <стойност> <оператор> <стойност> GOTO <номер на ред>
        // 20    PRINT     <стойност>
        // 30     READ    <име на променлива>
        // 40     GOTO    <номер на ред>

        let mut line = code
            .split_whitespace()
            .map(|x| x.to_string())
            .collect::<Vec<String>>();
        let mut num;
        match &line[0].parse::<u16>() {
            Ok(x) =>  {
                num = x;
                if line.len()==1
                {  
                    return Err(InterpreterError::SyntaxError {
                        code: code.to_string(),
                    });
                }
            },
            Err(_) => {
                return Err(InterpreterError::SyntaxError {
                    code: code.to_string(),
                })
            }
        };


        match line[1].as_str() {
            "IF" => {
                if line.len() != 7 {
                    return Err(InterpreterError::SyntaxError {
                        code: code.to_string(),
                    });
                }
            }
            "PRINT" => {
                if line.len() != 3 {
                    return Err(InterpreterError::SyntaxError {
                        code: code.to_string(),
                    });
                }
            }
            "READ" => {
                if line.len() != 3 {
                    return Err(InterpreterError::SyntaxError {
                        code: code.to_string(),
                    });
                }

                let mut var = line[2].chars().next().unwrap();
                if !var.is_uppercase() {
                    return Err(InterpreterError::SyntaxError {
                        code: code.to_string(),
                    });
                }
            }
            "GOTO" => {
                if line.len() != 3 {
                    return Err(InterpreterError::SyntaxError {
                        code: code.to_string(),
                    });
                }
                match line[2].parse::<u16>() {
                    Ok(_) => (),
                    Err(_) =>    return Err(InterpreterError::SyntaxError {
                        code: code.to_string(),
                    }),
                };
            }
            _ => {
                return Err(InterpreterError::SyntaxError {
                    code: code.to_string(),
                })
            }
        };

        self.lines.insert(line[0].parse::<u16>().unwrap(), line[1..].to_vec());
        Ok(())
    }
}
// Не забравяйте lifetime анотацията
impl<'a, R: Read, W: Write> Interpreter<'a, R, W> {
    /// Оценява `value` като стойност в контекста на интерпретатора:
    ///
    /// - Ако `value` е низ, който започва с главна буква (съгласно `char::is_uppercase`), търсим
    ///   дефинирана променлива с това име и връщаме нейната стойност.
    ///   -> Ако няма такава, връщаме `InterpreterError::UnknownVariable` с това име.
    /// - Ако `value` е валидно u16 число, връщаме числото
    ///   -> Иначе, връщаме `InterpreterError::NotANumber`vp с тази стойност
    ///
    pub fn eval_value(&self, value: &str) -> Result<u16, InterpreterError> {
        let firstLetter= value.chars().next().unwrap();
        if firstLetter.is_uppercase() {
            if !self.vars.contains_key(&value.to_string()) {
                return Err(InterpreterError::UnknownVariable{ name: value.to_string()})
            }
            return Ok(*self.vars.get(&value.to_string()).unwrap());
        }
        match value.parse::<u16>() {
            Ok(x) => return Ok(x),
            Err(_) => return Err(InterpreterError::NotANumber{value: value.to_string()}),
        };

    }
}
// Не забравяйте lifetime анотацията
impl<'a, R: Read, W: Write> Interpreter<'a, R, W> {
    /// Функцията започва да изпълнява редовете на програмата в нарастващ ред. Ако стигне до GOTO,
    /// скача на съответния ред и продължава от него в нарастващ ред. Когато вече няма ред с
    /// по-голямо число, функцията свършва и връща `Ok(())`.
    ///
    /// Вижте по-долу за отделните команди и какви грешки могат да върнат.
    ///
    pub fn run(&mut self) -> Result<(), InterpreterError> {


        //#  zashto ne napravat prev() na nqkoq struktura (pone ne namerih nikude imashe nqkuv
        // range za binary tree map ama toi pa vzima excluded na lqva granica) , ta trqbva da prava tova :(
        let mut sorted_keys:Vec<u16>=Vec::new();
        for key in self.lines.keys()  {
            sorted_keys.push(*key);
        }
        
        sorted_keys.sort();
        
        let mut keys_indexes : HashMap<u16,u16> = HashMap::new();
        for i in 0..sorted_keys.len() {
            keys_indexes.insert(sorted_keys[i], i as u16);
        }
        // for (key,value)  in &keys_indexes{
        //     println!("{} {} ", key,value);
        // }

        let mut curr:usize=0;

        while curr < sorted_keys.len()  {
        
        // command_and_arguments {
        //      0         1         2             3       4           5
        //      IF      <стойност> <оператор> <стойност> GOTO <номер на ред>
        //    PRINT     <стойност>
        //      READ    <име на променлива>
        //      GOTO    <номер на ред>
            //print!("while");
            let line_num :&u16 = &sorted_keys[curr];
            let command_and_arguments = self.lines.get(line_num).unwrap().clone();
            //println!("{}",command_and_arguments.len());
            match command_and_arguments[0].as_str() {   
                "PRINT" => {
                    //println!("print");
                    if command_and_arguments[1].chars().next().unwrap().is_uppercase() {
                        if !self.vars.contains_key(&command_and_arguments[1]) {
                            return Err(InterpreterError::RuntimeError{ line_number: *line_num, message: "nevalidna komanda tuk".to_string() });
                        }
                        match self.output.write(format!("{}\n",self.vars.get(&command_and_arguments[1]).unwrap().to_string()).as_bytes()){
                            Ok(_) => { curr += 1 ;
                            continue;
                            } 
                            Err(mess) => return Err(InterpreterError::IoError(mess)),
                        };
                    }

                   // println!("here");

                    match self.output.write(format!("{}\n",command_and_arguments[1]).as_bytes()){
                    Ok(_) => {
                        curr += 1 ;
                        continue;
                    },
                    Err(mess) => return Err(InterpreterError::IoError(mess)),
                };
                   
                }
                "READ" => {
                    let mut buf:Vec<u8> = Vec::new();
                    match self.reader.read_until('\n' as u8,&mut buf){
                      Ok(_) => (),
                      Err(mess) => return Err(InterpreterError::IoError(mess)),
                  }
                  let mut n = buf.len()-1;
                  while n >= 0 {
                    if buf[n].is_ascii_control(){
                        buf.pop();
                        n-=1;
                        continue;
                    }
                    break;
                  }
                 // println!("{}",buf.len());
                  for i in &buf {
                      if !(*i >= '0' as u8 && *i<='9' as u8) {
                          return Err(InterpreterError::RuntimeError{ line_number: *line_num, message: "nevalidna komanda tuk".to_string() });
                      }
                  }
                  let mut number=0;
                  let mut out:String=String::new();
                  for i in &buf {
                    out+=&format!("{}",*i as char)[..];
                  }
                  match out.parse::<u16>(){
                    Ok(x) => { 
                        number=x;
                    },
                    Err(_) => return Err(InterpreterError::RuntimeError{ line_number: *line_num, message: "nevalidna komanda tuk".to_string() }),
                    };

                
                //println!("{}",number);
                // match u16::from_str_radix(&buf, 16) {
                //         Ok(_) => () ,
                //         Err(_) => return Err(InterpreterError::RuntimeError{ line_number: *line_num, message: "nevalidna komanda tuk".to_string() }),
                //     };
                // let mut number = u16::from_str_radix(&buf, 16).unwrap();
                
                
                // println!();
                // println!();
                // println!();
                // println!();
                // println!("{}",buf.len());
                // println!("{}",num);
                    // match buf.parse::<u16>() {
                    //     Ok(_num) => { num= _num; } ,
                    //     Err(_) => return Err(InterpreterError::RuntimeError{ line_number: *line_num, message: "nevalidna komanda tuk".to_string() }),
                    // }
                    self.vars.insert(command_and_arguments[1].clone(), number);
                   // println!("read");
                    curr+=1;
                    continue;
                },
                "GOTO" => {
                    if !keys_indexes.contains_key(&command_and_arguments[1].parse::<u16>().unwrap()) {
                        return Err(InterpreterError::RuntimeError{ line_number: *line_num, message: "nevalidna komanda tuk".to_string() })
                    }
                    curr=*keys_indexes.get(&command_and_arguments[1].parse::<u16>().unwrap()).unwrap() as usize;
                    continue;
                },
                "IF" => {
                    let mut valueLhs: u16=0;
                    let mut valueRhs:u16=0;

                    match self.eval_value(command_and_arguments[1].as_str()) {
                        Ok(_num) => { valueLhs =_num },
                        Err(_) => return Err(InterpreterError::RuntimeError{ line_number: *line_num, message: "nevalidna komanda tuk".to_string() }),
                    }

                    match self.eval_value(command_and_arguments[3].as_str()) {
                        Ok(_num) => { valueRhs =_num },
                        Err(_) => return Err(InterpreterError::RuntimeError{ line_number: *line_num, message: "nevalidna komanda tuk".to_string() }),
                    }

                    match command_and_arguments[2].as_str() {
                        "<" => {
                            if valueLhs < valueRhs {
                                if !keys_indexes.contains_key(&command_and_arguments[5].parse::<u16>().unwrap()) {
                                    return Err(InterpreterError::RuntimeError{ line_number: *line_num, message: "nevalidna komanda tuk".to_string() })
                                }
                                curr=*keys_indexes.get(&command_and_arguments[5].parse::<u16>().unwrap()).unwrap() as usize;
                                continue;
                            }
                            else {
                                curr+=1;
                                continue;
                            }
                        }
                        ">" => {
                            if valueLhs > valueRhs {
                                if !keys_indexes.contains_key(&command_and_arguments[5].parse::<u16>().unwrap()) {
                                    return Err(InterpreterError::RuntimeError{ line_number: *line_num, message: "nevalidna komanda tuk".to_string() })
                                }
                                curr=*keys_indexes.get(&command_and_arguments[5].parse::<u16>().unwrap()).unwrap() as usize;
                                continue;
                            }
                            else {
                                curr+=1;
                                continue;
                            }
                        }
                        "=" => {
                            if valueLhs == valueRhs {
                                if !keys_indexes.contains_key(&command_and_arguments[5].parse::<u16>().unwrap()) {
                                    return Err(InterpreterError::RuntimeError{ line_number: *line_num, message: "nevalidna komanda tuk".to_string() })
                                }
                                curr=*keys_indexes.get(&command_and_arguments[5].parse::<u16>().unwrap()).unwrap() as usize;
                                continue;
                            }
                            else {
                                curr+=1;
                                continue;
                            }
                        }
                        _ => ()
                    };

                },
                _ => ()
            }

        }
    
        Ok(())
    }
}

macro_rules! assert_match {
    ($expr:expr, $pat:pat) => {
        let result = $expr;

        if let $pat = result {
            // all good
        } else {
            assert!(false, "Expression {:?} does not match the pattern {:?}", result, stringify!($pat));
        }
    }
}

#[test]
fn test_basic_1() {
    // Забележете `b""` -- низ от байтове
    let input: &[u8] = b"1\n2\n";
    let mut output = Vec::<u8>::new();
    let mut interpreter = Interpreter::new(input, &mut output);

    interpreter.add("10 READ A").unwrap();
    interpreter.add("20 READ B").unwrap();
    interpreter.add("30 PRINT A").unwrap();
    interpreter.add("40 PRINT B").unwrap();

    interpreter.run().unwrap();
    assert_eq!(interpreter.eval_value("A").unwrap(), 1_u16);
    assert_eq!(String::from_utf8(output).unwrap(), "1\n2\n");
}

#[test]
fn test_basic_2() {
    let input: &[u8] = b"";
    let mut output = Vec::<u8>::new();
    let mut interpreter = Interpreter::new(input, &mut output);

    assert_match!(interpreter.add("10 PRINT"), Err(InterpreterError::SyntaxError { .. }));
}

pub struct NotBuffered {}

impl std::io::Read for NotBuffered {
    fn read(&mut self, _buf: &mut [u8]) -> std::io::Result<usize> {
        Ok(0)
    }
}

#[test]
fn test_not_buffered() {
    let input = NotBuffered {};
    let mut output = Vec::<u8>::new();
    let mut interpreter = Interpreter::new(input, &mut output);

    interpreter.add("10 PRINT 10").unwrap();
    interpreter.run().unwrap();
}