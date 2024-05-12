USE movies;

--2015-lqto 

--4.1 (moe resh)
SELECT S.STARNAME
FROM STARSIN as s
JOIN MOVIE as m on s.MOVIETITLE = m.TITLE
WHERE S.STARNAME NOT LIKE '%a' AND
	  m.INCOLOR='Y' and s.STARNAME IN (SELECT DISTINCT s.STARNAME
									   FROM STARSIN as s
									   JOIN MOVIE as m on s.MOVIETITLE = m.TITLE
									   WHERE S.STARNAME NOT LIKE '%a' AND m.INCOLOR='N')

--a) x  // greshka !='%a' oznachava razlichno ot string a ne matchva pattern + ednovremmeno hem da e cveten hem da e bql v where-a
--b) x // tuk e obedinenie ili sa igrali v cherno beli ili v cvetni a nie iskame da sa igrali i v dvata
--c) x // vrushta poveche ot edno query starname= a i nqma join prosto gi slepq (natural join)
--SELECT DISTINCT STARNAME
--FROM STARSIN
--INNER JOIN MOVIE ON MOVIETITLE=TITLE and MOVIEYEAR=YEAR
--WHERE STARNAME NOT LIKE '%a' and INCOLOR='Y'
--	  AND STARNAME= (SELECT STARNAME
--					 FROM STARSIN,MOVIE
--					 WHERE INCOLOR='n')


--d) v
SELECT STARNAME
FROM STARSIN
JOIN MOVIE ON TITLE=MOVIETITLE AND MOVIEYEAR=YEAR
WHERE STARNAME NOT LIKE '%a' AND INCOLOR='Y'
INTERSECT
SELECT STARNAME
FROM STARSIN
JOIN MOVIE ON TITLE=MOVIETITLE AND MOVIEYEAR=YEAR
WHERE INCOLOR='N'


--4.2

--moe resh
SELECT m.NAME,YEAR(m.BIRTHDATE) as Birth_year, COUNT(DISTINCT me.STUDIONAME) as cnt_studio
FROM MOVIESTAR as m
LEFT JOIN STARSIN as si on m.NAME=si.STARNAME
LEFT JOIN MOVIE as me on si.MOVIETITLE=me.TITLE and si.MOVIEYEAR=me.YEAR
GROUP BY m.NAME,YEAR(m.BIRTHDATE)
HAVING COUNT(DISTINCT si.MOVIETITLE)  <= 5

--SELECT *
--FROM MOVIESTAR as m
--LEFT JOIN STARSIN as si on m.NAME=si.STARNAME
--LEFT JOIN MOVIE as me on si.MOVIETITLE=me.TITLE and si.MOVIEYEAR=me.YEAR
--ORDER BY m.NAME

--a) x // syntax error , there is no birthdate.year function in sql format


--b) x // nqma year(birthdate) v group by syntax error ( no e nai pravilno)
--SELECT name , YEAR(birthdate),COUNT(DISTINCT STUDIONAME)
--FROM MOVIESTAR
--left outer join STARSIN on NAME=STARNAME
--left join MOVIE on MOVIETITLE=TITLE and MOVIEYEAR=YEAR
--group by NAME
--having count(title) <=5

--c) x //nqma year(birthdate) v group by syntax error
--d) x // syntax error, having without group by