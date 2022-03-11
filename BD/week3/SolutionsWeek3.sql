--I.1--
SELECT distinct si.STARNAME as name
FROM STARSIN si , MOVIESTAR ms
WHERE si.STARNAME=ms.NAME
and ms.GENDER='F'
and exists ( SELECT 1
FROM MOVIEEXEC me, MOVIE m
WHERE me.CERT#=m.PRODUCERC#
and me.NAME=si.STARNAME
)
--I.2--
SELECT ms.NAME
FROM MOVIESTAR ms
WHERE ms.NAME not in (Select NAME
FROM MOVIEEXEC )

--I.3--
SELECT m.TITLE
FROM MOVIE m
WHERE m.LENGTH > ANY (SELECT strwrs.LENGTH 
FROM MOVIE strwrs 
WHERE strwrs.TITLE='Star Wars')

--I.4--
SELECT mex.NAME as producerName, m.TITLE as filmName
FROM MOVIEEXEC mex, MOVIE m
WHERE mex.CERT#=m.PRODUCERC#
and mex.NETWORTH > ANY (
SELECT mie.NETWORTH
FROM MOVIEEXEC mie
WHERE mie.NAME='Merv Griffin'
)

--II.1--
SELECT distinct pr.maker
FROM product pr, pc p
WHERE pr.model=p.model
and p.speed>500

--II.2--
SELECT p.code ,p.model,p.price
FROM printer p
WHERE p.price >= ALL ( SELECT p1.price FROM printer p1)

--II.3--
SELECT *
FROM laptop l
Where l.speed < ALL (SELECT p.speed FROM pc p)

--II.4--
SELECT p.model,p.price
FROM (SELECT model,price
FROM pc
UNION
SELECT model, price
FROM printer
UNION 
Select model, price
FROM laptop
) as p
WHERE p.price >= ALL (Select pC.price FROM pc pC)
and p.price >= ALL (Select l.price FROM laptop l)
and p.price >= ALL (Select pr.price FROM printer pr)

--II.5--
SELECT p.maker
FROM printer pr, product p
WHERE pr.model=p.model
and pr.color='Y'
and pr.price <= ALL ( SELECT pr1.price
FROM printer pr1, product p1
WHERE pr1.model=p1.model
and pr1.color='Y')


--II.6--
SELECT p.maker
FROM pc pC, product p
WHERE pC.model=p.model
and pC.ram <= ALL ( SELECT pc1.ram FROM pc pc1)
and pC.speed >= ALL ( SELECT pC1.speed 
FROM pc pC1
WHERE pC1.ram <= ALL ( SELECT pC1.ram FROM pc pC1))



--III.1--
SELECT distinct cl.country as COUNTRY
FROM CLASSES cl
WHERE cl.NUMGUNS >= ALL (SELECT cl1.NUMGUNS FROM CLASSES cl1)

--III.2--
SELECT distinct cl.CLASS
FROM CLASSES cl, SHIPS sh, OUTCOMES ou
WHERE (cl.CLASS=sh.CLASS and sh.NAME=ou.SHIP)
and sh.NAME IN ( SELECT ou1.SHIP FROM OUTCOMES ou1 WHERE ou1.RESULT='sunk')

--III.3--
SELECT sh.NAME, cl.CLASS
FROM SHIPS sh, CLASSES cl
WHERE sh.CLASS=cl.CLASS
and cl.BORE=16;

--III.4--
SELECT distinct bat.NAME
FROM BATTLES bat,OUTCOMES ou,SHIPS sh
Where bat.NAME=ou.BATTLE and ou.SHIP=sh.NAME
and sh.CLASS='Kongo'

--III.5--
SELECT  sh.CLASS,sh.NAME
FROM SHIPS sh, CLASSES cl
WHERE sh.CLASS=cl.CLASS
and cl.NUMGUNS >= ALL (SELECT cl1.NUMGUNS
FROM SHIPS sh1, CLASSES cl1
where sh1.CLASS=cl1.CLASS
and cl.BORE=cl1.BORE)
order by sh.CLASS


SELECT *
FROM CLASSES