use std::{process::Output, str::FromStr};

#[derive(Debug)]
pub enum Color {
    RGB { red: u8, green: u8, blue: u8 },
    HSV { hue: u16, saturation: u8, value: u8 },
}

impl Color {
    pub fn new_rgb(red: u8, green: u8, blue: u8) -> Color {
        Self::RGB { red, green, blue }
    }

    pub fn new_hsv(hue: u16, saturation: u8, value: u8) -> Color {
        if hue > 360 || saturation > 100 || value > 100 {
            panic!("Invalid input");
        }

        Self::HSV {
            hue,
            saturation,
            value,
        }
    }

    // Color::from_str("#ff00ff") -> Color::RGB { red: 255, green: 0, blue: 255 }
    // Color::from_str("hsv(360,100%,50%)") -> Color::HSV { hue: 360, saturation: 100, value: 50 }
    pub fn from_str(input: &str) -> Self {
        let arr_char = input.chars().collect::<Vec<char>>();
        let res = match &arr_char[0] {
            '#' => {
                let red = u8::from_str_radix(&input[1..=2], 16).unwrap_or_else(|e| panic!("{}", e));
                let green =
                    u8::from_str_radix(&input[3..=4], 16).unwrap_or_else(|e| panic!("{}", e));
                let blue =
                    u8::from_str_radix(&input[5..=6], 16).unwrap_or_else(|e| panic!("{}", e));
                Color::RGB {
                    red: red,
                    green: green,
                    blue: blue,
                }
            }
            'h' => {
                let mut t = input
                    .split(&[',', '%', '(', ')'][..])
                    .collect::<Vec<&str>>();

                //["hsv", "360", "100", "", "50", "", ""] <- that is it what we received after above operation
                let hue = u16::from_str(t[1]).unwrap_or_else(|e| panic!("{}", e));
                let saturation = u8::from_str(t[2]).unwrap_or_else(|e| panic!("{}", e));
                let value = u8::from_str(t[4]).unwrap_or_else(|e| panic!("{}", e));

                Color::HSV {
                    hue: hue,
                    saturation: saturation,
                    value: value,
                }
            }
            _ => panic!("Not found converting between given input: &str and Color !"),
        };
        res
    }
}

pub fn add(left: usize, right: usize) -> usize {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }

    #[test]
    fn basic_test() {
        let a = Color::from_str("#ff0010");
        let b = match &a {
            Color::RGB { red, green, blue } => (*red, *green, *blue),
            _ => (0, 0, 0),
        };

        assert_eq!(b, (255, 0, 16));

        let a = Color::from_str("hsv(360,100%,50%)");
        let b = match &a {
            Color::HSV {
                hue,
                saturation,
                value,
            } => (*hue, *saturation, *value),
            _ => (0, 0, 0),
        };

        assert_eq!(b, (360, 100, 50));
    }

    #[test]
    fn edge_cases_test() {
        let a = Color::from_str("#000000");
        let b = match &a {
            Color::RGB { red, green, blue } => (*red, *green, *blue),
            _ => (1, 1, 1),
        };

        assert_eq!(b, (0, 0, 0));

        let a = Color::from_str("#ffffff");
        let b = match &a {
            Color::RGB { red, green, blue } => (*red, *green, *blue),
            _ => (0, 0, 0),
        };

        assert_eq!(b, (255, 255, 255));

        let a = Color::from_str("hsv(0,0%,0%)");
        let b = match &a {
            Color::HSV {
                hue,
                saturation,
                value,
            } => (*hue, *saturation, *value),
            _ => (1, 1, 1),
        };

        assert_eq!(b, (0, 0, 0));

        let a = Color::from_str("hsv(360,100%,100%)");
        let b = match &a {
            Color::HSV {
                hue,
                saturation,
                value,
            } => (*hue, *saturation, *value),
            _ => (0, 0, 0),
        };

        assert_eq!(b, (360, 100, 100));
    }

    #[test]
    fn random_test() {
        let a = Color::from_str("hsv(261,69%,43%)");
        let b = match &a {
            Color::HSV {
                hue,
                saturation,
                value,
            } => (*hue, *saturation, *value),
            _ => (0, 0, 0),
        };

        assert_eq!(b, (261, 69, 43));

        let a = Color::from_str("#597cfd");
        let b = match &a {
            Color::RGB { red, green, blue } => (*red, *green, *blue),
            _ => (0, 0, 0),
        };

        assert_eq!(b, (89, 124, 253));
    }

    #[test]
    fn just_to_know_test() {
        //let a = Color::from_str("hsv(360,256%,0%)"); //panic /w mes: "number too large to fit in target type"
        //let b = Color::from_str("sv(360,255%,0%)"); //panic /w mes: "Not found converting between given input: &str and Color ! "
        //let c = Color::from_str("hsv(-360,255%,0%)"); //panic /w mes: "invalid digit found in string "
        assert_eq!(1,1);
    }
}
