use std::collections::HashSet;

#[derive(Debug)]
pub enum GameStatus {
    InProgress,
    Won,
    Lost,
}

#[derive(Debug)]
pub enum GameError {
    NotInAlphabet(char),
    WrongLength { expected: usize, actual: usize },
    GameIsOver(GameStatus),
}

#[derive(Debug)]
pub struct Game {
    pub status: GameStatus,
    pub attempts: u8,
    pub target_word: Vec<char>,
    pub alphabet: HashSet<char>,
    pub history: Vec<Word>,
}

#[derive(Debug, Clone, Copy)]
pub enum Letter {
    FullMatch(char),
    PartialMatch(char),
    NoMatch(char),
    Unknown(char),
}

#[derive(Debug, Clone)]
pub struct Word {
    pub letters: Vec<Letter>,
}
impl Game {
    /// Конструира нова игра с думи/букви от дадената в `alphabet` азбука. Alphabet е просто низ,
    /// в който всеки символ е отделна буква, който вероятно искате да си запазите някак за после.
    ///
    /// Подадената дума с `word` трябва да има само букви от тази азбука. Иначе очакваме да върнете
    /// `GameError::NotInAlphabet` грешка с първия символ в `word`, който не е от азбуката.
    ///
    /// Началното състояние на играта е `InProgress` а началния брой опити `attempts` е 0.
    ///
    pub fn new(alphabet: &str, word: &str) -> Result<Self, GameError> {
        let mut _alphabet: HashSet<char> = HashSet::new();
        
        // we used these because &str has u8 chars in it and for example the cyrilic char: 'с' has |_||_|
        // empty spaces in the begining which isn't correct in the context of the task
        // when we represent each symbol as char, char has 4 byte capacity , 'c' is with length one
        let alphabet_vec=alphabet.chars().collect::<Vec<char>>();
        let word_vec=word.chars().collect::<Vec<char>>();


        for c in alphabet_vec {
            _alphabet.insert(c);
        }
        for c in &word_vec {
            if !_alphabet.contains(c) {
                return Err(GameError::NotInAlphabet(*c));
            }
        }
        Ok(Game {
            status: GameStatus::InProgress,
            attempts: 0,
            target_word: word_vec.clone(),
            alphabet: _alphabet.clone(),
            history: vec![Word {
                letters: vec![Letter::Unknown('_'); word_vec.len()],
            }],
        })
    }

    /// Опитва се да познае търсената дума. Опита е в `guess`.
    ///
    /// Ако играта е приключила, тоест статуса ѝ е `Won` или `Lost`, очакваме да върнете
    /// `GameIsOver` със статуса, с който е приключила.
    ///
    /// Ако `guess` има различен брой букви от търсената дума, очакваме да върнете
    /// `GameError::WrongLength`. Полето `expected` на грешката трябва да съдържа броя букви на
    /// търсената дума, а `actual` да е броя букви на опита `guess`.
    ///
    /// Ако `guess` има правилния брой букви, но има буква, която не е от азбуката на играта,
    /// очакваме `GameError::NotInAlphabet` както по-горе, с първия символ от `guess`, който не е
    /// от азбуката.
    ///
    /// Метода приема `&mut self`, защото всеки валиден опит (такъв, който не връща грешка) се
    /// запазва в играта за по-нататък. Метода връща `Word`, което описва освен самите символи на
    /// `guess`, и как тези символи са се напаснали на търсената дума. Също така инкрементира
    /// `attempts` с 1.
    ///
    /// След опита за напасване на думата, ако всички букви са уцелени на правилните места,
    /// очакваме `state` полето да се промени на `Won`. Иначе, ако `attempts` са станали 5,
    /// състоянието трябва да е `Lost`.
    ///
    pub fn guess_word(&mut self, guess: &str) -> Result<Word, GameError> {
        match &self.status {
            GameStatus::Lost => return Err(GameError::GameIsOver(GameStatus::Lost)),
            GameStatus::Won => return Err(GameError::GameIsOver(GameStatus::Won)),
            _ => {}
        };
        let guess_vec = guess.chars().collect::<Vec<char>>();
        if guess_vec.len() == self.target_word.len() {
            for c in &guess_vec {
                if !self.alphabet.contains(c) {
                    return Err(GameError::NotInAlphabet(*c));
                }
            }
            let mut attempt_word: Word = Word {
                letters: Vec::new(),
            };
            let mut count: usize = 0;
            for i in 0..=self.target_word.len() - 1 {
                if self.target_word[i] == guess_vec[i] {
                    attempt_word.letters.push(Letter::FullMatch(guess_vec[i]));
                    count += 1;
                } else if self.target_word.contains(&guess_vec[i]) {
                    attempt_word
                        .letters
                        .push(Letter::PartialMatch(guess_vec[i]));
                } else {
                    attempt_word.letters.push(Letter::NoMatch(guess_vec[i]));
                }
            }

            self.attempts += 1;

            //user guessed the word
            if self.attempts <= 5 && count == self.target_word.len() {
                self.status = GameStatus::Won;
            }
            //user didn't guess the word and ran out of moves
            else if self.attempts == 5 {
                self.status=GameStatus::Lost;
            }

            self.history.push(attempt_word.clone());
            return Ok(attempt_word.clone());


        } else {
            return Err(GameError::WrongLength {
                expected: self.target_word.len(),
                actual: guess_vec.len(),
            });
        }
    }
}

use std::fmt;

impl fmt::Display for Word {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let mut output = String::new();
        for letter in &self.letters {
            match letter {
                Letter::FullMatch(ch) => {
                    //let to_upper= String::from_iter(ch.to_uppercase());
                    output.push_str(&format!("[{}]", String::from_iter(ch.to_uppercase()))[..])
                },
                Letter::PartialMatch(ch) => {
                     output.push_str(&format!("({})", String::from_iter(ch.to_uppercase()))[..]) 
                    },
                Letter::NoMatch(ch) => {
                    output.push_str(&format!(">{}<", String::from_iter(ch.to_uppercase()))[..])
                },
                Letter::Unknown(ch) => {
                    output.push_str(&format!("|{}|", String::from_iter(ch.to_uppercase()))[..])
                },
            }
        }

        write!(f, "{}", output)
    }
}

impl fmt::Display for Game {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let mut output = String::new();
        for word in &self.history {
            output.push_str(&format!("{}\n", word)[..]);
        }

        //cuts last '\n'
        write!(f, "{}", &output[0..output.len() - 1])
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_basic() {
        let english_letters = "abcdefghijklmnopqrstuvwxyz";
    
        // Конструираме по два различни начина, just in case -- няма причина да не работи и с двата.
        assert!(Game::new(english_letters, "!!!").is_err());
        let mut game = Game::new(&String::from(english_letters), "abc").unwrap();
    
        assert!(matches!(game.status, GameStatus::InProgress));
        assert_eq!(game.attempts, 0);
        assert_eq!(game.to_string(), "|_||_||_|");
        assert_eq!(game.guess_word("abc").unwrap().to_string(), "[A][B][C]");
    }
    #[test]
    fn bulgarian_letter(){
        let bulgarian_letters = "АаБбВвГгДдЕеЖжЗзИиЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЬьЮюЯя";
        let mut game2 = Game::new(bulgarian_letters, "к").unwrap();
        assert_eq!(game2.to_string(),"|_|"); //|_|
        assert_eq!(game2.guess_word("с").unwrap().to_string(),">С<"); //>С<
        assert_eq!(game2.guess_word("а").unwrap().to_string(),">А<"); //>А<
        assert_eq!(game2.attempts,2); //2
        assert!(matches!(game2.status,GameStatus::InProgress)); //Inprogress
        assert_eq!(game2.guess_word("а").unwrap().to_string(),">А<"); //>А<
        assert_eq!(game2.guess_word("а").unwrap().to_string(),">А<"); //>А<
        assert_eq!(game2.guess_word("к").unwrap().to_string(),"[К]"); //[К]
        assert_eq!(game2.attempts,5); //5
        assert!(matches!(game2.status,GameStatus::Won)); //Won
        assert_eq!(game2.to_string(),"|_|\n>С<\n>А<\n>А<\n>А<\n[К]");
    }
    #[test]
    fn bulgarian_letters(){
        let bulgarian_letters = "АаБбВвГгДдЕеЖжЗзИиЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЬьЮюЯя";
        assert!(Game::new(bulgarian_letters, "üßбунароко").is_err());
        assert!(Game::new(bulgarian_letters, "юженятъгцюяьн").is_ok());

        let mut game3 = Game::new(bulgarian_letters, "имамбаялдъ").unwrap();
        assert_eq!(game3.to_string(),"|_||_||_||_||_||_||_||_||_||_|"); //|_||_||_||_||_||_||_||_||_||_|
        assert!(matches!(Game::new(bulgarian_letters, "имамбаялдъ").unwrap().guess_word("имамбаялдяя").unwrap_err(),GameError::WrongLength {expected: 10, actual: 11}));
   
        assert!(matches!(Game::new(bulgarian_letters, "имамбаялдъ").unwrap().guess_word("имамбаялдß").unwrap_err(),GameError::NotInAlphabet('ß')));
        
        assert_eq!(game3.guess_word("имамчушкар").unwrap().to_string(),"[И][М][А][М]>Ч<>У<>Ш<>К<(А)>Р<"); //[И][М][А][М]>Ч<>У<>Ш<>К<(А)>Р<
        assert_eq!(game3.guess_word("имамяаялко").unwrap().to_string(),"[И][М][А][М](Я)[А][Я][Л]>К<>О<"); //[И][М][А][М](Я)[А][Я][Л]>К<>О<
        assert_eq!(game3.guess_word("имамиаялмъ").unwrap().to_string(),"[И][М][А][М](И)[А][Я][Л](М)[Ъ]"); //[И][М][А][М](И)[А][Я][Л](М)[Ъ]
        assert_eq!(game3.guess_word("имамбаялдъ").unwrap().to_string(),"[И][М][А][М][Б][А][Я][Л][Д][Ъ]"); //[И][М][А][М][Б][А][Я][Л][Д][Ъ]

        assert_eq!(game3.attempts,4);
        assert!(matches!(game3.guess_word("имамбаялдъ").unwrap_err(),GameError::GameIsOver(GameStatus::Won)));
    
    }

    #[test]
    fn bulgarian_letters_2(){
        let bulgarian_letters = "АаБбВвГгДдЕеЖжЗзИиЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЬьЮюЯя";
        let mut game3 = Game::new(bulgarian_letters, "имамбаялдъ").unwrap();

        assert_eq!(game3.guess_word("имамчушкар").unwrap().to_string(),"[И][М][А][М]>Ч<>У<>Ш<>К<(А)>Р<"); //[И][М][А][М]>Ч<>У<>Ш<>К<(А)>Р<
        assert_eq!(game3.guess_word("имамяаялко").unwrap().to_string(),"[И][М][А][М](Я)[А][Я][Л]>К<>О<"); //[И][М][А][М](Я)[А][Я][Л]>К<>О<
        assert_eq!(game3.guess_word("имамиаялмъ").unwrap().to_string(),"[И][М][А][М](И)[А][Я][Л](М)[Ъ]"); //[И][М][А][М](И)[А][Я][Л](М)[Ъ]
        assert_eq!(game3.guess_word("имамиаялмъ").unwrap().to_string(),"[И][М][А][М](И)[А][Я][Л](М)[Ъ]"); //[И][М][А][М](И)[А][Я][Л](М)[Ъ]
        assert_eq!(game3.guess_word("имамиаялмъ").unwrap().to_string(),"[И][М][А][М](И)[А][Я][Л](М)[Ъ]"); //[И][М][А][М](И)[А][Я][Л](М)[Ъ]
        

        assert_eq!(game3.attempts,5);
        assert!(matches!(game3.guess_word("имамбаялдъ").unwrap_err(),GameError::GameIsOver(GameStatus::Lost)));

        assert_eq!(game3.to_string(),"|_||_||_||_||_||_||_||_||_||_|\n[И][М][А][М]>Ч<>У<>Ш<>К<(А)>Р<\n[И][М][А][М](Я)[А][Я][Л]>К<>О<\n[И][М][А][М](И)[А][Я][Л](М)[Ъ]\n[И][М][А][М](И)[А][Я][Л](М)[Ъ]\n[И][М][А][М](И)[А][Я][Л](М)[Ъ]"); 

    }

    #[test]
    fn german_letters(){
        let german_letters = "abcdefghijklmnopqrstuvwxyzäöüß";
        let mut game = Game::new(german_letters, "süß").unwrap();


        assert_eq!(game.guess_word("füß").unwrap().to_string(),">F<[Ü][SS]"); //>F<[Ü][SS]
        assert_eq!(game.guess_word("äöü").unwrap().to_string(),">Ä<>Ö<(Ü)"); //>Ä<>Ö<(Ü)
        assert_eq!(game.guess_word("füs").unwrap().to_string(),">F<[Ü](S)"); //>F<[Ü](S)

        assert!(matches!(game.status,GameStatus::InProgress));
        assert_eq!(game.attempts,3);
        assert!(matches!(game.guess_word("fü😊").unwrap_err(),GameError::NotInAlphabet('😊')));
    }
}
