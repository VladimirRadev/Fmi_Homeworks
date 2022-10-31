use std::mem;

//use simple_matrix::Matrix;
fn main() {
    //    let arr: [u32; 3]= [1,2,3];
    //    let nested_arr: [[u32;3];2] = [
    //     [1,2,3],
    //     [2,69,4],
    //    ];

    // let tuple: (bool,i32,f32,f64,bool) = (true,2,2.12,3.144,true);
    // println!("{:?}",tuple.4); //true expected

    // let tosho: &str = "Kukata!";
    // if tosho.len() % 2 == 0 {
    //     print!("tosho e cheten\n");

    // }
    // else {
    //     println!("tosho e necheten") ;
    // }

    // let mut var: i32 = 69;
    // var +=2;
    // var -=2;

    // if var == 69 {
    //     println!("chukam qko malki kurvi \n\n\n");
    // }
    // else {
    //     println!("ne chukam oshte");
    // }
    // let mat: Matrix<i32>= Matrix::from_iter(2,2,[0,1,2,0]);
    // let mut col: i8 = 0;

    // for i in & mat {
    //     col+=1;
    //     print!("{} ",i);
    //     if col as usize % mat.cols() == 0
    //     {
    //         println!();
    //         col=0;
    //     }
    // }

    // let x = {
    //     let a:String = String::from("TOSHO");
    //     let b = a.clone();
    //     println!("{:?}",a);
    //     b
    // };
    // println!("{:?}",x);

    // let a = 5;
    // let b = 4;
    // let bigger = if a > b {a} else {b};

    // print!("{}",bigger);

    //let add2 = |a, b| { a + b };

    //println!("add1: {}\nadd2: {}", add1(1, 2), add2(1, 2));
    //println!("{:?}",concat("tosho", "kukata"));

    // let concat = |a: &str ,b: &str| -> String {
    //     if a.contains('s') && !b.contains('k') {
    //         a.to_string()
    //     } else {
    //         b.to_string()
    //     }
    //  };
    // println!("{:?}",concat("tosjo","kukata"));

    // let a = "HELLO";
    // let b = a;
    // print!("{} {} ",a,b);

    // let s = String::from("hello"); // Дефинираме s

    // takes_ownership(s);            // Стойността на s се мести във функцията и
    //                                // затова не е валидна след този ред.

    // let s1 = String::from("hello");
    // let (s2, len) = calculate_length(s1);

    // println!("The length of '{}' is {}. {} ", s2, len);

    // let s1 = String::from("hello");
    // let len = calculate_length(&s1);

    // println!("The length of '{}' is {}.", s1, len);
    // let mut s:String = String::from("Hello");
    // change(&mut s);
    // println!("{:?}",s);

    // let mut s = String::from("hello");

    // let r1 = &mut s;
    // println!("{}", r1);

    // let r2 = &mut s;
    // println!("{}  ", r2);

    // let s1 = String::from("hello");
    // let r = &s1;

    // let s2 = s1;

    // println!("{}  ",r);

    // let s = &String::from("hello");

    // let s=&s;
    // println!("{}", s);

    // let mut s = String::from("hello");
    // {
    //     {
    //         let r = &mut s;
    //         greet_cookies(r);
    //     }

    //     println!("{}", s);
    // }

    // let s = String::from("hello, world");
    // let r1 = &s[..];
    // let r2 = &r1[1..=4];

    // println!("{}", r2);

    // let arr: [u32;3] = [1,69,3];
    // let arr_slice = &arr[1..];
    // println!("{:?}",arr_slice);

    // let mut vec = vec![1,2,3];
    // vec.push(56);
    // vec.push(32);
    // vec.pop();
    // let vec_slice= &vec[..];
    // println!("{:?}",vec_slice);

    // let  slice: &mut [i32;3] = &mut [1, 2, 3];
    // slice[2]=32_i32;
    // println!("{:?}", &slice[1..=2]);
    // let user= User{
    //     username: String::from("Gosho"),
    //     email: String::from("tosho"),
    //     sign_in_count : 32
    // };
    // let user1= user.clone();
    // let user2= User{
    //     username: String::from("Anastas Gerdjikov"),
    //     ..user1
    // };
    // let user3 = User::new(String::from("Boyan"), String::from("Petrov"));
    // println!("{:?}",user3);

    // let mut rect= Rectangle::new(23.3, 2.3);
    // let area=rect.area();
    // rect.change();
    // let area=rect.area();

    // print!("{}",area);

    //    let some = IpAddrKind::ChangeIp(String::from("baz"), String::from("sas"), 1.3);

    //    println!("{:?}",&some);


//     let some = Some(5);
//     let some_string=Some("Tosho");
//     let abcent_number: Option<i32>=None;

  
// println!("{:?}", some);
// println!("{:?}", some_string);
// println!("{:?}", mem::size_of::<String>());

// let x:Option<i32> = None;
// let y = match x {
//     Some(val) => val * val,
//     None => 1
// };

// print!("{:?}",y);


// let string = String::from("abc");
// let mut chars = string.chars();

// for c in chars {
//     println!("{:?}", c);
// }

// let nums = [1,2,3,4];
// let mut iter_num=nums.iter();
// if let Some(n)=iter_num.next(){
//     print!("{}",n);
//     while let Some(n)=iter_num.next(){
//      print!(",and {}",n);   
//     }
// }
    // let cake:&[&str] = &["vanilla", "strawberry", "chocolate"];
    
    // match cake {
    //     []         => println!("Turns out it's a lie :/"),
    //     [one_item] => println!("One slice is better than nothing"),
    //     _          => println!("Wow, that's a lotta slices!")
    // }





// if let x = Some(2) {
//     println!("Yup! x = {:?}", x)
// }

// if let x = Some(1) {
//     println!("Also yup! x = {:?}", x)
// }


// enum Message {
//     Quit,
//     Move { x: i64, y: i64 },
//     Write(String),
//     ChangeColor(i64, i64, i64),
// }

// let message = Message::Move { x: 3, y: 4 };
// println!("{}", message);  // boom pri enumi trqbva da polzvame match i da pokriem vsichki sluchai



// let arr = &["едно", "две", "три"];

// let mut iter = arr.iter();
// while let Some(val) = iter.next() {
//     println!("{}", val);
// }

// let iter = arr.iter();
// for val in iter {

//     println!("{}", val);
// }

// let arr_iter: Vec<&i32> = [1,2,3,4,5].iter().collect();
// for val in arr_iter{
//     if val %2 ==0 {
//         println!("{} e chetno ",val);
//     }
//     else{
//         println!("{} e nechechetno ",val);

//     }
// }

// let mut arr_iter = [3,2,1,3].iter();
// if let Some(val) = arr_iter.next()  {
//     print!("{}",val);
//     while let Some(val) = arr_iter.next() {
//         print!(", {}",val);
//     }
// }


    let sub_hi = &"Здравей! 😊"[0..6];
    println!("{:x?}", sub_hi.as_bytes());

   

        assert_eq!(add_two(2), 5);
 



}

fn add_two(x: i32) -> i32 { x + 2 }
// fn concat(a: & str, b: &str) -> String {
//     let mut res: String = String::from(a);
//     res.push_str(b);
//     a.to_string()
// }

// fn takes_ownership(some_string: String) {
//     println!("{}", some_string);
// } // some_string излиза от scope и се освобождава паметта.

// fn calculate_length(s: String) -> (String, usize) {
//     let length = s.len(); // len() връща дължината на String.
//     (s, length)
// }

// fn calculate_length(s: &String) -> usize {
//     s.len()
// }

// fn change ( s_change: &mut String) {
//     s_change.push_str(" world!");
// }

// #[derive(Clone,Debug,Default)]
// struct User{
//     username: String,
//     email: String,
//     sign_in_count: u64
// }

// impl User  {
//     fn new(username:String,email:String) ->Self {
//         Self {username, email,..Self::default()}
//     }
// }

// #[derive(Clone,Debug,Default)]
// struct Rectangle { width: f64, height: f64 }

// impl Rectangle {
//     fn new(width: f64, height: f64) ->Self
//     {
//         Self { width, height}
//     }
//     fn area(&mut self) -> f64 {
//         self.width * self.height
//     }
//     fn change(&mut self){
//         self.width=20_f64;
//     }
// }

// mod network {
//     fn init() { todo!() }
// }

// #[derive(Debug)]
// enum IpAddrKind {
//     V4(String),
//     V6 {x: i64, y: i64},
//     ChangeIp (String ,String, f64)
// }


   