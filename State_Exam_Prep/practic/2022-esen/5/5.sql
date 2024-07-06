USE movies;

--2022-esen

--5.1)
--MOE RESH
SELECT m.TITLE,m.LENGTH
FROM MOVIE m
where m.INCOLOR='Y'
and m.LENGTH is not null
and m.TITLE NOT IN (SELECT me.TITLE
					FROM MOVIE me
					where me.INCOLOR='Y'
					and me.LENGTH >= ALL( SELECT LENGTH
											FROM MOVIE 
											where INCOLOR='Y'
											and LENGTH is not null))
--5.2)
--moe resh

SELECT s.NAME
FROM STUDIO as s
LEFT JOIN MOVIE as m on s.NAME=m.STUDIONAME
where m.TITLE is null
UNION
SELECT s.NAME
FROM STUDIO as s
JOIN MOVIE as m on s.NAME=m.STUDIONAME
GROUP BY s.NAME
HAVING COUNT(DISTINCT m.YEAR) = 1

--a) x // vzimash ot tablicata studio kolona year, koqto e v movie
--á) x // vzimam vsichki studia koito imat veche filmi ot movie tablicata
--â) v
SELECT name
FROM Studio
LEFT JOIN Movie ON name = studioname
GROUP BY name
HAVING COUNT(DISTINCT year) <= 1;
--ã) x // vzemi studia kudeto not exists filmi ( tova vinagi she dava false tui kato v movie vinagi she ima neshto)
