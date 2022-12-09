
use homework2::*;
fn main() {
    let english_letters = "abcdefghijklmnopqrstuvwxyz";
    let bulgarian_letters = "АаБбВвГгДдЕеЖжЗзИиЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЬьЮюЯя";
   // let symbols = "!<#?/0123456789,.'\"';:-+)(*&^%$@}{[]|\\>~`";
    let mut game1 = Game::new(english_letters, "foobar").unwrap();
    let mut game2 = Game::new(bulgarian_letters, "к").unwrap();

    game2.guess_word("с").unwrap(); //<c>
    game2.guess_word("а").unwrap(); //<a>
    println!("{}", game2.attempts); //2
    println!("{:?}", game2.status); //Inprogress
    game2.guess_word("а").unwrap(); //<a>
    game2.guess_word("а").unwrap(); //<a>
    game2.guess_word("к").unwrap(); //<к>
    println!("{}", game2.attempts); //5
    println!("{:?}", game2.status); //Won
    println!("{}", game2); //Won

    let german_letters = "abcdefghijklmnopqrstuvwxyzäöüß";
    let mut game = Game::new(german_letters, "süß").unwrap();

    println!("{}", game.guess_word("füß").unwrap());
    println!("{}", game.guess_word("äöü").unwrap());
    println!("{}", game.guess_word("füs").unwrap());
   // >F<[Ü][SS]

     println!("{}", game1.guess_word("oopsie").unwrap());

    let english_letters = "abcdefghijklmnopqrstuvwxyz";
    let mut game = Game::new(english_letters, "rebus").unwrap();

    println!("{}-> {} -> {:?}", game,game.attempts,game.status);
    //|_||_||_||_||_|

    game.guess_word("route").unwrap();
    println!("{} -> {} -> {:?}", game,game.attempts,game.status);
    //|_||_||_||_||_|
    //[R]>O<(U)>T<(E)

    game.guess_word("rebus").unwrap();
    println!("{} -> {} -> {:?}", game,game.attempts,game.status);
    //|_||_||_||_||_|
    //[R]>O<(U)>T<(E)
    //[R][E][B][U][S]

    let english_letters = "abcdefghijklmnopqrstuvwxyz";
    let mut game = Game::new(english_letters, "rebus").unwrap();

    game.guess_word("route").unwrap();
    game.guess_word("rebus").unwrap();

    assert_eq!(
        game.to_string(),
        "|_||_||_||_||_|\n[R]>O<(U)>T<(E)\n[R][E][B][U][S]"
    );

    let mut game3 = Game::new(bulgarian_letters, "имамбаялдъ").unwrap();
    println!("{}",game3.guess_word("имамчушкар").unwrap());
    println!("{}",game3.guess_word("имамяаялко").unwrap());

    println!("{}",game3.guess_word("имамиаялмъ").unwrap());

    println!("{}",game3.guess_word("имамбаялдъ").unwrap());

    

}