USE movies;





SELECT *
FROM MOVIESTAR
LEFT JOIN STARSIN ON NAME=STARNAME


--esen 2010 zad 2.1
SELECT DISTINCT ms.NAME
FROM MOVIESTAR as ms
LEFT JOIN STARSIN as si on ms.NAME=si.STARNAME
WHERE ms.NAME NOT IN (SELECT DISTINCT ms.NAME
					  FROM MOVIESTAR as ms
					  LEFT JOIN STARSIN as si on ms.NAME=si.STARNAME
					  WHERE si.MOVIEYEAR > 1970)
			  OR si.MOVIEYEAR IS NULL
--a) x , ne izkluchvame tozi chovek da ima i film sled 1970
--b) x, shte mi vzeme vsichki koito imat film sled 1970 i posle grupira (abs non sense)
--c) v
SELECT NAME 
FROM MOVIESTAR
WHERE NAME NOT IN (SELECT DISTINCT STARNAME
					FROM STARSIN
					WHERE MOVIEYEAR > 1970)
--d) x , ne izkluchvame  da ima sled 1970
--SELECT M.NAME
--FROM MOVIESTAR M
--WHERE EXISTS (SELECT 1 FROM STARSIN S WHERE S.STARNAME = M.NAME AND S.MOVIEYEAR <=1970);


--esen 2010 zad 2.2

SELECT * FROM MOVIESTAR JOIN STARSIN on NAME=STARNAME


--a) x , natural join + bez distinct
--b) v
SELECT ms.NAME,MIN(si.MOVIEYEAR - YEAR(ms.BIRTHDATE)) AS DEBUT_AGE
FROM MOVIESTAR as ms
INNER JOIN STARSIN as si on ms.NAME=si.STARNAME
GROUP BY ms.NAME;


--c) x , nqma kak da imame having i vutre non boolean type
--SELECT ms.NAME,si.MOVIEYEAR - YEAR(ms.BIRTHDATE) AS DEBUT_AGE
--FROM MOVIESTAR as ms
--INNER JOIN STARSIN as si on ms.NAME=si.STARNAME
--GROUP BY ms.NAME
--HAVING MIN(si.MOVIEYEAR); <- error


--d) x , having vmesto where