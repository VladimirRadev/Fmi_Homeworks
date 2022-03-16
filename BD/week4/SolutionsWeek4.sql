--I.1--
SELECT m2.TITLE,mex1.NAME
FROM MOVIE m2 JOIN MOVIEEXEC mex1 on
m2.PRODUCERC#=mex1.CERT#
WHERE m2.PRODUCERC# in (
SELECT mex.CERT#
FROM MOVIE m1 JOIN MOVIEEXEC mex
on m1.PRODUCERC#= mex.CERT#
WHERE m1.TITLE='Star Wars'
)

--I.2--
SELECT distinct mex1.NAME
FROM MOVIE as mov1 JOIN MOVIEEXEC mex1 on
mov1.PRODUCERC#=mex1.CERT#
WHERE mov1.TITLE in
(SELECT si.MOVIETITLE FROM STARSIN si WHERE si.STARNAME='Harrison Ford') 


--I.3--
SELECT  distinct s.NAME as studioName, si.STARNAME
FROM MOVIE me JOIN STUDIO s on me.STUDIONAME=s.NAME
JOIN STARSIN si on me.TITLE=si.MOVIETITLE
order by  studioName

--I.4--
SELECT  si.STARNAME, mex.NETWORTH,mi.TITLE
FROM MOVIE mi JOIN MOVIEEXEC mex on mi.PRODUCERC#=mex.CERT#
JOIN STARSIN si on mi.TITLE=si.MOVIETITLE
where mex.NETWORTH >= ALL ( SELECT mex2.NETWORTH FROM MOVIEEXEC mex2)

--I.5--
SELECT ms.NAME as name , si.MOVIETITLE as movieTitle
FROM MOVIESTAR ms LEFT JOIN STARSIN si on ms.NAME=si.STARNAME
WHERE si.MOVIETITLE is NULL

--II.1--
SELECT p.maker, p.model, p.type
FROM product p LEFT JOIN (SELECT l.model FROM laptop l 
UNION
SELECT pC.model FROM pc pC
UNION SELECT pr.model FROM printer pr) as models on p.model=models.model
WHERE models.model is NULL

--II.2--
SELECT distinct p.maker
FROM laptop l RIGHT JOIN product p on l.model=p.model
WHERE l.code is not NULL
INTERSECT 
SELECT distinct p.maker
FROM printer pr RIGHT JOIN product p on pr.model=p.model
WHERE pr.code is not NULL

--II.3--
SELECT distinct l1.hd
FROM laptop l1, laptop l2
WHERE l1.hd=l2.hd
and l1.code < l2.code

--II.4--
SELECT p.maker
FROM product p LEFT JOIN pc pC on p.model=pC.model
WHERE p.model is NULL

--III.1--












SELECT *
FROM pc;