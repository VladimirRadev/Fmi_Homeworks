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
FROM SHIPS sh LEFT JOIN CLASSES cl on sh.CLASS=cl.CLASS

--III.2--
SELECT  *
FROM  CLASSES cl left join Ships sh on (sh.CLASS=cl.CLASS or ((sh.CLASS is null) and cl.CLASS in 
(
SELECT sh.NAME
FROM SHIPS sh
)))

--III.3--

SELECT cl.COUNTRY as COUNTRY, sh.NAME as shipName
FROM CLASSES cl JOIN SHIPS sh on cl.CLASS=sh.CLASS 
LEFT JOIN OUTCOMES ou on sh.NAME=ou.SHIP
WHERE ou.SHIP is NULL
order by cl.COUNTRY,sh.NAME

--III.4--
SELECT sh.NAME as ShipName
FROM SHIPS sh LEFT JOIN CLASSES cl on sh.CLASS=cl.CLASS
WHERE cl.NUMGUNS >= 7 and sh.LAUNCHED=1916


--III.5--
SELECT  sh.NAME , ou.BATTLE,bat.DATE
FROM SHIPS sh Right join OUTCOMES ou on sh.NAME=ou.SHIP
LEFT JOIN BATTLES bat on ou.BATTLE=bat.NAME
WHERE ou.RESULT='sunk'
order by ou.BATTLE

--III.6--
SELECT sh.NAME,cl.DISPLACEMENT,sh.LAUNCHED 
FROM SHIPS sh LEFT JOIN CLASSES cl on sh.CLASS=cl.CLASS
WHERE sh.NAME=sh.CLASS

--III.7--
SELECT cl.CLASS,cl.TYPE,cl.COUNTRY,cl.NUMGUNS,cl.BORE,cl.DISPLACEMENT
FROM CLASSES cl LEFT JOIN SHIPS sh on cl.CLASS=sh.CLASS
WHERE sh.CLASS is NULL

--III.8--
SELECT sh.NAME,cl.DISPLACEMENT,cl.NUMGUNS,ou.RESULT
FROM SHIPS sh LEFT JOIN CLASSES cl on sh.CLASS=cl.CLASS
LEFT JOIN OUTCOMES ou on sh.NAME=ou.SHIP
WHERE ou.BATTLE='North Atlantic'









SELECT *
FROM SHIPS;