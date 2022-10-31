#[cfg(test)]
mod tests {
    use homework_1::*;
    #[test]
    fn test_basic() {
        let color1 = Color::new_rgb(0, 0, 0);
        assert_eq!(color1.unwrap_rgb().0, 0);
        assert_eq!(&color1.to_string()[0..1], "#");

        let color2 = Color::new_hsv(0, 0, 0);
        assert_eq!(color2.unwrap_hsv().0, 0);

        assert_eq!(color1.invert().unwrap_rgb().0, 255);
    }

    #[test]
    fn invert_bacic() {
        let new_rgb = Color::new_rgb(255, 255, 255);
        let new_hsv= Color::new_hsv(360, 5, 5);

        assert_eq!(new_rgb.unwrap_rgb(),(255,255,255));
        assert_eq!(new_rgb.invert().unwrap_rgb(),(0,0,0));


        assert_eq!(new_hsv.unwrap_hsv(),(360,5,5));
        assert_eq!(new_hsv.invert().unwrap_hsv(),(0,95,95));


        assert_eq!(Color::new_hsv(0, 50, 0).invert().to_string(),"hsv(360,50%,100%)");
        assert_eq!(Color::new_hsv(255, 10, 15).invert().to_string(),"hsv(105,90%,85%)");
        
        
        assert_eq!(Color::new_rgb(0, 255, 0).invert().to_string(),"#ff00ff");
        assert_eq!(Color::new_rgb(123, 0, 254).invert().to_string(),"#84ff01");

    }
}
