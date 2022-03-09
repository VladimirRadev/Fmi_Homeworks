--I.1--
SELECT ms.NAME as actorName
FROM STARSIN si, MOVIESTAR ms
WHERE (si.STARNAME=ms.NAME)
and ms.GENDER='M'
and si.MOVIETITLE='The Usual Suspects'

--I.2--
SELECT si.STARNAME as actorName
FROM MOVIE m, STARSIN si
WHERE m.TITLE=si.MOVIETITLE
and m.STUDIONAME='MGM'
and m.YEAR=1995

--I.3--
SELECT distinct me.NAME
FROM MOVIE m, MOVIEEXEC me
WHERE m.PRODUCERC#=me.CERT#
and m.STUDIONAME='MGM'

--I.4--
SELECT m.TITLE
FROM MOVIE m
Where m.LENGTH > ANY (SELECT LENGTH
FROM MOVIE
Where TITLE='Star Wars')

--I.5--
SELECT me.NAME
FROM MOVIEEXEC me
Where me.NETWORTH > ANY (SELECT NETWORTH
FROM MOVIEEXEC
Where NAME='Stephen Spielberg')

--I.6--
SELECT m.TITLE
FROM MOVIE m,MOVIEEXEC mex
WHERE m.PRODUCERC#=mex.CERT#
and mex.NAME IN (SELECT me.NAME
FROM MOVIEEXEC me
Where me.NETWORTH > ANY (SELECT NETWORTH
FROM MOVIEEXEC
Where NAME='Stephen Spielberg'))


--II.1--
SELECT p.maker as MAKER , l.speed as MHz
FROM laptop l, product p
WHERE l.model=p.model
and l.hd>=9

--II.2--
SELECT pr.model as MODEL, p.price as PRICE
FROM product pr , pc p
WHERE pr.model=p.model
and pr.maker='B'
UNION
SELECT pr.model as MODEL, pri.price as PRICE
FROM product pr, printer pri
WHERE pr.model=pri.model
and pr.maker='B'
UNION 
SELECT pr.model as MOdel , lap.price as PRICE
FROM product pr, laptop lap
WHERE pr.model=lap.model
and pr.maker='B'

--II.3--
SELECT distinct pr.maker
FROM product pr
WHERE pr.type='Laptop'
EXCEPT
SELECT distinct pr.maker
FROM product pr
WHERE pr.type='PC'

--II.4--
SELECT distinct p1.hd
FROM pc p1, pc p2
WHERE p1.code!=p2.code
and p1.hd=p2.hd

--II.5--
SELECT distinct p1.model,p2.model
FROM pc p1, pc p2
WHERE p1.model!=p2.model
and
p1.speed=p2.speed
and p1.ram=p2.ram
and p1.model<p2.model

--II.6--

SELECT *
FROM product pr,pc p1
WHERE pr.model=p1.model
and p1.speed>=400

--III.1--
SELECT distinct s.NAME
FROM SHIPS s, CLASSES cl
WHERE s.CLASS=cl.CLASS
and cl.DISPLACEMENT>50000

--III.2--
SELECT distinct sh.NAME,cl.DISPLACEMENT,cl.NUMGUNS
FROM CLASSES cl, SHIPS sh, OUTCOMES ou
WHERE (cl.CLASS=sh.CLASS and sh.NAME=ou.SHIP)
and ou.BATTLE='Guadalcanal'

--III.3--
SELECT distinct cl1.COUNTRY
FROM CLASSES cl1
WHERE cl1.COUNTRY IN
(
SELECT  c2.COUNTRY
FROM CLASSES c2
WHERE c2.TYPE='bb'
INTERSECT
SELECT  c3.COUNTRY
FROM CLASSES c3
WHERE c3.TYPE='bC'
)

--III.4--
Select ou1.SHIP
FROM OUTCOMES ou1
WHERE ou1.RESULT='damaged'
INTERSECT
(
Select ou2.SHIP
FROM OUTCOMES ou2
WHERE ou2.RESULT='ok'
UNION
Select ou3.SHIP
FROM OUTCOMES ou3
WHERE ou3.RESULT='sunk'
)



SELECT *
FROM OUTCOMES