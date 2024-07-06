USE movies;

--2023-esen

--5.1)
SELECT STARNAME
FROM STARSIN 
JOIN MOVIESTAR on STARNAME=NAME
WHERE MOVIEYEAR <= 2000
and GENDER='F'
INTERSECT
SELECT STARNAME
FROM STARSIN 
JOIN MOVIESTAR on STARNAME=NAME
WHERE MOVIEYEAR >= 2001
and GENDER='F'



--5.2)

--moe resh
					--SELECT *
					--FROM STUDIO as s
					--JOIN MOVIE as m on s.NAME=m.STUDIONAME
SELECT S.NAME
FROM STUDIO as s
JOIN MOVIE as m on s.NAME=m.STUDIONAME
WHERE m.INCOLOR='N'
GROUP BY s.NAME
HAVING SUM(m.LENGTH) > (SELECT MAX(m.LENGTH)
						FROM STUDIO as so
						JOIN MOVIE as m on so.NAME=m.STUDIONAME
						WHERE so.NAME=s.NAME)



--a) x // vzima samo necvetnite , a se kazva che trabva max(ot kakuvto i da e (no matter the color )
--á) x // agregate function in where clause, i.e syntax error
--â) v
SELECT name
FROM Studio
WHERE (SELECT SUM(length)
FROM Movie
WHERE incolor = 'N'
AND studioname = Studio.name)
> (SELECT MAX(length)
FROM Movie
WHERE studioname = Studio.name);
--ã) x // vzima nai dulgiq film kato cqlo v cqlata tablica a ne nai dulgiq na tova studio


