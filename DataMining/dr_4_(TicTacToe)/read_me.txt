***Интелигентни системи Софтуерно инженерство курс 4 зимен семестър Домашно 4 ***
Владимир Радев фн.62530 група 1

-За задачата съм използвал minimax алгоритъмът с alpha-beta pruning
-В началото играта пита кой искаме да започне първи и ние чрез въвеждане на [P/p] или [C/c] избираме съответно ние или компютъра да започне първи
-Компютърър е maximizer , а ние (играчът) сме minimizer
-Ако сме избрали първи да е компютърът , той играе най-добрия ход за него ( maximizer) , дъската се update-va и изобразява на конзолата и е наш ред
-Въвеждаме първо ред (от 1 до 3) и колона (от 1 до 3)
-Играта приключва с три възможни състоянния -
		1) maximizer( computer) печели
		2) minimizer( ние ) печели
		3) играта завършва наравно
-Ако изберем ние да сме първи играта протича аналогично само, че сме ние първи на ход на всяка стъпка
-Алгоритъма е оптимален понеже се гледа също така и дълбочината на която един от двамата играчи печели ( а не само utilitito)
-Utility-то се изчислява : 
			-> 10 - depth ( za maximizer -"computer")
			-> -10 + depth ( za minimizer - "ние <=> player")
			-> 0 при равни



		-В зипа може да откриете:
			->IS_DR4_fn_62530.cpp - кодът на задачата на (Ц++)
			->IS_DR4_fn_62530.exe - екзето от ръннатия код