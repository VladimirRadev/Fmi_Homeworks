***Интелигентни системи Софтуерно инженерство курс 4 зимен семестър Домашно 2 ***
Владимир Радев фн.62530 група 1

- За решаването на задачата съм minConflict() алгоритъма и предоставения псевдокод от упражненията. Използвал съм 3те масива с брой царици съответно по ред , главни диагонали (d1) и вторични диагонали (d2) : queensPerRow, queensPerD1, queensPerD2;
- Също така имам и масивът nQueens - който пази като индекси колоните от 0 до n , а стоностите за всеки индекс е на кой ред се намира всяка царица в текущото състояние
- Инициализирам с рандом ред за всяка цараца за всяка колона ( също тествах и с ходя на коня но ,беше по-бавно , затова оставих да се позиционират цариците на рандом - [върви за 10000 за <=1сек])
- Aлгоритъма търси редът на царицата която е с наай-много конфликти в момента и я слага на реда с най-малко конфликти , като ако има 2 или повече с равни конфликти , се взима на рандом една от тях , за да се предотврати зацикляне - също така се помни последната колона ("previousCol" в кода) , която е взета от алгоритъма и нея не се разглежда (за да се предотврати зацикляне ))
- Ако имаме два реда или повече реда с най-малко конфликти , царицата се поставя на рандом ред
- Алгоритъма работи докато царицата с най-много конфликти има 0 конфликти <=> борда е нареден
- В текущото състояние кодът принтира борда ( с '*' и '_')  , за да подготвите кода за judge-a трябва да:
	1) коментирате ред 283 nonAutomatedTestingPrinting(); 
	2) и да откоментирате ред 284 automatedTestingPrinting();
	3) да компилирате локално и да вземете .exe за judge-a ( аз работя с VS code и g++ (Rev6, Built by MSYS2 project) 13.1.0
											Copyright (C) 2023 Free Software Foundation, Inc.
											This is free software; see the source for copying conditions.  There is NO
											warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.)

		-В зипа може да откриете:
			->IS_DR2_fn_62530.cpp - кодът на задачата на (Ц++)
			->IS_DR2_fn_62530.exe - екзето от ръннатия код
			->proof_of_grade.PNG - това което ми изкарва judge-a ( без човката за slow compatible languages) - 100% final grade
			