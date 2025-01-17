﻿#pragma once
//Разполагате с информация за футболен клуб и по - конкретно поредица от номера на екипите на всички футболисти, които са играли някога за този отбор.Възможно е да срещате повтарящи се номера, това е защото в даден момент футболист е играл с номер Х и след напускането му друг футболист е започнал да играе със същия номер Х.Вашата задача е да намерите най - малкият номер на екип(цяло положително число), който никога не е слаган на екипа на футболист от отбора.Тъй като информацията е писана преди време, трябва да внимавате с това че може да срещнете отрицателни числа(които не трябва да вземате под внимание) между номерата на екипите.
//
//Input Format
//
//На първия ред на стандартния вход ви е дадено положително число N.На втория ред - са дадени N на брой цели числа
//
//Constraints
//
//
//Output Format
//
//На първия и единствен ред на стандартния изход трябва да изведете търсеният първи липсващ номер на екип.
//
//Sample Input 0
//
//15
//9 2 6 5 - 1 1 4 - 20 3 2 2 1 - 8 - 7 - 5
//
//Sample Output 0
//7
//
//Explanation 0
//Първият номер, който не е използваn за екип на футболист на отбора е 7
//
//
//Sample Input 1
//4
//1 5 4 3
//
//Sample Output 1
//2