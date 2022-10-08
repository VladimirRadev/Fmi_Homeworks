fn main() {
    let n:u32 = 21;
    for i in 0..n {
        println!("Fibonachi at index {} is {}",i,fib(i));
    }
}
pub fn fib(n: u32) -> u32 {
    if n == 0 
    {
        return 0;
    }
    if n == 1
    {
        return 1;
    }
    let mut a: u32 = 0;
    let mut b: u32 = 1;
    let mut index: u32 = 2;
    let mut res: u32 = 0;
    while index <= n 
    {
        res = a + b;
        a = b;
        b = res;
        
        index+=1;
    }
    res    
}

