// fn identify<T>(value: T) -> T {
//     value
// }
// struct Point<T,U>{
//     x: T,
//     y: U
// }
// #[derive(Debug)]
// enum Message <T,A> {
//     Text(T),
//     Action(A)
// }

// impl<T,U> Point<T,U>{
//     fn mixup<V,W>(self,other: Point<V,W>) -> Point<T,W>{
//         Point { x: self.x, y: other.y }
//     }
// }

// use std::process::Output;

// trait ToJson {
//     fn to_json(&self) -> String;
// }
// impl ToJson for String {
//     fn to_json(&self) -> String {
//         format!("\"{}\"", self)
//     }
// }
// impl ToJson for i32 {
//     fn to_json(&self) -> String {
//         format!("{}", self)
//     }
// }

// fn to_json<T: ToJson>(value: T) -> String {
//     value.to_json()
// }
// trait NonDispatchable {
//     // Статичните функции не могат да се викат през trait object.
//     fn foo()
//     where
//         Self: Sized,
//     {
//     }
//     // Self типа не се знае докато не се изпълни програмата.
//     fn returns(&self) -> Self
//     where
//         Self: Sized;
//     // `other` може да има друг конкретен тип (concrete type) спрямо receiver-a self.
//     fn param(&self, other: Self)
//     where
//         Self: Sized,
//     {
//     }
//     // Обобщените типове не са съвместими с vtable.
//     fn typed<T>(&self, x: T)
//     where
//         Self: Sized,
//     {
//     }
// }
// trait Add {
//     type Output;
//     fn add(self, rhs: Self) -> Self::Output;
// }
// impl Add for i32 {
//     type Output = i64;
//     fn add(self, rhs: i32) -> i64 {
//         (self + rhs) as i64
//     }
// }

struct Celsius(f64);
struct Fahrenheit(f64);
struct Kelvin(f64);

fn room_temperature() -> Fahrenheit {
    Fahrenheit(68.0)
}

impl From<&Celsius> for Kelvin {
    fn from(t: &Celsius) -> Kelvin {
        Kelvin(t.0 + 273.12)
    }
}
impl From<Fahrenheit> for Kelvin {
    fn from(t: Fahrenheit) -> Kelvin {
        Kelvin(t.0 / 18.0)
    }
}
#[derive(Debug)]
struct Student {
name: String,
faculty_number: String,
}

use std::str::FromStr;

impl FromStr for Student {
    type Err = String;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s.split(", ").collect::<Vec<_>>().as_slice() {
            [name, faculty_number] => {
                let name = name.to_string();
                let faculty_number = faculty_number.to_string();

                Ok(Self { name, faculty_number })
            },
            _ => Err(String::from("🤷🤷🤷")),
        }
    }
}
fn main() {
    // let a = Point{x: 2.2, y:2.4};
    // let n = Point{x: 2, y: "Hell"};

    // let p = n.mixup(Point{x: 5, y: "kur"});

    // println!("{:?} , {:?}",p.x,p.y);

    // let a = String::from("sss").to_json();
    // println!("{}",a);
    // let b = Some(String::from("ss"));
    // let c:Option<u8> = None;

    // let tosho=Add::add(2, 3);
    // let s=to_json(3.3); // gurmi shoto nqma implementiran for f64

    // let a = Celsius(22.3);
    // let mut b:Kelvin= Kelvin::from(room_temperature());
    // println!("From cels:{} -> {} Kelvin",a.0,b.0);

    // let x = i32::from_str("-13");
    // let y = u8::from_str("323");
    // let z = f32::from_str("5e-3");

    // println!("{:?}\n{:?}\n{:?}", x, y, z);

    // let u= "09".parse::<i32>();
    // println!("{:?}",u);


}
