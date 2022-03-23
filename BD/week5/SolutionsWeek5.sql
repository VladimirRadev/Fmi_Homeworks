--I.1--
SELECT AVG (speed) as avgSpeed
FROM pc

--I.2--
SELECT pr.maker ,AVG (lap.screen) as  screen
FROM laptop lap JOIN product pr on lap.model=pr.model
GROUP by pr.maker

--I.3--
SELECT AVG (lap.speed)
FROM laptop lap
WHERE lap.price > 1000

--I.4--
SELECT CAST ( round (AVG (p.price),2) AS decimal (8,2))
FROM pc p JOIN product pr on p.model=pr.model
where pr.maker='A'

--I.5-- 
SELECT AVG ( allPrices.price) as price
FROM (SELECT lap.price
FROM laptop lap JOIN product pr on lap.model=pr.model
WHERE pr.maker='B'
UNION ALL
SELECT p.price
FROM pc p JOIN product pr on p.model=pr.model
WHERE pr.maker='B') as allPrices

--I.6--
SELECT p.speed as speed,AVG (p.price) as price
FROM pc p
GROUP by p.speed

--I.7--
SELECT pr.maker , COUNT ( p.code) as number
FROM pc p JOIN product pr on p.model=pr.model
GROUP by pr.maker
HAVING COUNT(p.code) >= 3

--I.8--
SELECT pr.maker,MAX (p.price) as price
FROM pc p JOIN product pr on p.model=pr.model
WHERE p.price >= ALL (SELECT pc1.price
FROM pc pc1)
GROUP by pr.maker

--I.9--
SELECT p.speed, AVG (p.price) as avgPrice
FROM pc p
GROUP by p.speed
HAVING p.speed > 800

--I.10--
SELECT pr.maker as maker ,AVG (p.hd) as hdd
FROM pc p LEFT JOIN product pr on p.model=pr.model
WHERE pr.maker in ( SELECT pr.maker
FROM printer prin JOIN product pr on prin.model=pr.model)
GROUP by pr.maker


--II.1--
SELECT COUNT (cl.class) as fight_ships
FROM CLASSES cl
WHERE cl.TYPE='bb'

--II.2--
SELECT cl.CLASS, AVG(cl.NUMGUNS) as avgGuns
FROM CLASSES cl
WHERE cl.TYPE='bb'
GROUP by cl.CLASS

--II.3--
SELECT AVG(cl.NUMGUNS) as avgGuns
FROM CLASSES cl
WHERE cl.TYPE='bb'

--II.4--
SELECT cl.CLASS, MIN(sh.LAUNCHED) as firstDate, MAX (sh.LAUNCHED) as lastDate
FROM CLASSES cl JOIN SHIPS sh on cl.CLASS=sh.CLASS
GROUP by cl.CLASS

--II.5--
SELECT cl.CLASS , COUNT (sh.NAME) as shipsCount
FROM CLASSES cl JOIN SHIPS sh on cl.CLASS=sh.CLASS
JOIN OUTCOMES ou on sh.NAME=ou.SHIP
WHERE ou.RESULT='sunk'
GROUP by cl.CLASS
--HAVING count (sh.name) > 2

--II.6--
SELECT cl.CLASS , COUNT (sh.NAME) as shipsCount
FROM CLASSES cl JOIN SHIPS sh on cl.CLASS=sh.CLASS
JOIN OUTCOMES ou on sh.NAME=ou.SHIP
WHERE ou.RESULT='sunk' 
GROUP by cl.CLASS
HAVING (SELECT COUNT(sh.CLASS) FROM SHIPS sh WHERE sh.CLASS=cl.CLASS) > 2

--II.7--
SELECT cl.COUNTRY , AVG ( cl.BORE) as BORE
FROM CLASSES cl LEFT JOIN SHIPS sh on cl.CLASS=sh.CLASS
WHERE sh.CLASS is not null
GROUP by cl.COUNTRY






SELECT *
FROM CLASSES