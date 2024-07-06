USE  movies;
--2022-lqto

--5-1)
SELECT s.NAME,m.TITLE
FROM MOVIE m JOIN STUDIO s ON m.STUDIONAME=s.NAME
WHERE s.NAME in (SELECT STUDIONAME
				 FROM MOVIE
				 WHERE TITLE='The Usual Suspects' and year= 1995);

--5-2)

-- moe resh
SELECT ms.NAME --,si.STARNAME
FROM MOVIESTAR as ms
LEFT JOIN STARSIN as si on ms.NAME=si.STARNAME
WHERE si.STARNAME is NULL


--à) x // starsin vinagi she ima hora , ne moje count(*)=0
--á) v

SELECT ms.name, si.movietitle
FROM moviestar ms
LEFT JOIN starsin si
ON ms.name=si.starname
WHERE si.movietitle IS NULL;

--â) x // tuka e join toest vzimame zvezdi koito sa uchvastvali sus sig v pone edin film
--ã) x // pulna prostotiq