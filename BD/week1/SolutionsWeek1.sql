--I.1--
SELECT s.ADDRESS
FROM STUDIO s
WHERE s.NAME='Disney'

--I.2--
SELECT BIRTHDATE
FROM MOVIESTAR
WHERE NAME='Jack Nicholson'

--I.3--
SELECT STARNAME
FROM STARSIN
WHERE MOVIEYEAR=1980 
or UPPER(MOVIETITLE) like UPPER('%Knight%')

--I.4--
SELECT me.NAME
FROM MOVIEEXEC me
WHERE me.NETWORTH > 10000000

--I.5--
SELECT ms.NAME
FROM MOVIESTAR ms
WHERE ms.GENDER='M'
or ms.ADDRESS='Prefect Rd.'

--II.1--
SELECT p.model, p.speed as MHz ,p.hd as GB
FROM pc p
WHERE p.price<1200

--II.2--
SELECT distinct pr.maker
FROM product pr
WHERE pr.type='Printer'

--II.3--
SELECT model as MODEL, ram as RAM, screen AS SCREEN
FROM laptop
WHERE price > 1000

--II.4--
SELECT *
FROM printer
WHERE color='y'

--II.5--
SELECT model as MODEL , speed as MHz, hd as GB
FROM pc 
WHERE (cd='12x' or cd='16x')
and price<2000

--III.1--
SELECT cl.CLASS, cl.COUNTRY
FROM CLASSES as cl
WHERE cl.NUMGUNS < 10

--III.2--
SELECT sh.NAME as shipName
FROM SHIPS sh
WHERE sh.LAUNCHED<1918

--III.3--
SELECT ou.SHIP as shipName, ou.BATTLE as battleName
FROM OUTCOMES ou
Where ou.RESULT='sunk'

--III.4--
SELECT sh.NAME
FROM SHIPS as sh
WHERE sh.NAME=sh.CLASS

--III.5--
SELECT NAME
FROM SHIPS
WHERE UPPER(NAME) like UPPER('R%')

--III.6--
SELECT NAME
FROM SHIPS
WHERE UPPER(NAME) like UPPER('% %')
