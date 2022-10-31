#[derive(Debug)]
pub enum Color {
    RGB {
        red: u8,
        green: u8,
        blue: u8
    },
    HSV {
        hue: u16,
        saturation: u8,
        value: u8,
    }
}
impl Color {
    /// Конструира нова стойност от вариант `RGB` с дадените стойности за червено, зелено и синьо.
    ///
    pub fn new_rgb(red: u8, green: u8, blue: u8) -> Color {
        Color::RGB { red, green, blue }
    }

    /// Конструира нова стойност от вариант `HSV` с дадените стойности.
    ///
    /// В случай, че hue е над 360 или saturation или value са над 100, очакваме да `panic!`-нете с
    /// каквото съобщение си изберете.
    ///
    pub fn new_hsv(hue: u16, saturation: u8, value: u8) -> Color {
        if hue > 360 || saturation > 100 || value > 100 {
            panic!("Invalid data received in new_hsv() method");

        }
        else {
            Color::HSV { hue, saturation, value }
        }   
    }
}
impl Color {
    /// Ако `self` е `RGB`, тогава връщате неговите `red`, `green`, `blue` компоненти в този ред.
    /// Иначе, `panic!`-вате с каквото съобщение си изберете.
    ///
    pub fn unwrap_rgb(&self) -> (u8, u8, u8) {
        
        match self {
            Self::RGB { red, green, blue } => return (*red,*green,*blue),
            _ => panic!("Provided HSV as argument to unwrap_rgb() method !")
        };
    }

    /// Ако `self` е `HSV`, тогава връщате неговите `hue`, `saturation`, `value` компоненти в този
    /// ред. Иначе, `panic!`-вате с каквото съобщение си изберете.
    ///
    pub fn unwrap_hsv(&self) -> (u16, u8, u8) {
        match self{
            Self::HSV { hue, saturation, value } => return (*hue,*saturation,*value),
            _ => panic!("Provided RGB as argument to unwrap_hsv() method !")
        };
    }
}
impl Color {
    /// В случай, че варианта на `self` е `RGB`, очакваме низ със съдържание `#rrggbb`, където
    /// червения, зеления и синия компонент са форматирани в шестнадесетична система, и всеки от тях е
    /// точно два символа с малки букви (запълнени с нули).
    ///
    /// Ако варианта е `HSV`, очакваме низ `hsv(h,s%,v%)`, където числата са си напечатани в
    /// десетичната система, без водещи нули, без интервали след запетаите, вторите две завършващи на
    /// `%`.
    ///
    pub fn to_string(&self) -> String {
        let result=match self{
            Self::RGB { red, green, blue } => {
                 let res=format!("#{:02x}{:02x}{:02x}",*red,*green,*blue);
                 res
            },
            Self::HSV { hue, saturation, value } => {
                let res=format!("hsv({},{}%,{}%)",*hue,*saturation,*value);
                res
            }
        };
        result
    }
}
impl Color {
    /// Инвертира цвят покомпонентно -- за всяка от стойностите се взема разликата с максимума.
    ///
    
    pub fn invert(&self) -> Self {
        let res=match self {
            Self::RGB { red, green, blue } => {
                Self::RGB { red: red.abs_diff(255), green: green.abs_diff(255), blue: blue.abs_diff(255) }
            }
            Self::HSV { hue, saturation, value } => {
                Self::HSV { hue: hue.abs_diff(360), saturation: saturation.abs_diff(100), value: value.abs_diff(100) }
            }
        };
        res
    }
        
}


