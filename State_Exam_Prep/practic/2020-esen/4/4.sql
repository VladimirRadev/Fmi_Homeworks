USE movies;
--2020-esen

--4-1)

SELECT s.NAME,s.ADDRESS
FROM STUDIO as s
JOIN MOVIE as m on s.NAME=m.STUDIONAME
WHERE m.INCOLOR='Y'
INTERSECT
SELECT s.NAME,s.ADDRESS
FROM STUDIO as s
JOIN MOVIE as m on s.NAME=m.STUDIONAME
WHERE m.INCOLOR='N'
ORDER BY s.ADDRESS 

--4-2)
SELECT NAME,ADDRESS,AVG(LENGTH) as avg_lenght
FROM STUDIO 
LEFT JOIN MOVIE on NAME=STUDIONAME
GROUP BY NAME,ADDRESS
HAVING COUNT(DISTINCT TITLE) <= 3


--SELECT *
--FROM STUDIO 
--LEFT JOIN MOVIE on NAME=STUDIONAME


