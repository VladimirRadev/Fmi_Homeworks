USE ships;


--5.1)

--MOE RESH
SELECT DISTINCT c.CLASS--,s.CLASS,o.SHIP,o.RESULT
FROM CLASSES as c
LEFT JOIN SHIPS as s on c.CLASS=s.CLASS
LEFT JOIN OUTCOMES as o on s.NAME=o.SHIP
WHERE c.CLASS NOT IN (SELECT DISTINCT c.CLASS
					  FROM CLASSES as c
					  JOIN SHIPS as s on c.CLASS=s.CLASS
					  JOIN OUTCOMES as o on s.NAME=o.SHIP
					  WHERE o.RESULT = 'damaged')


--TQHNO RESH
SELECT class
FROM Classes
WHERE class NOT IN (SELECT class
FROM Ships
JOIN Outcomes ON name = ship
WHERE result = 'damaged');

--5.2)

--MOE RESH
SELECT c.CLASS, COUNT(DISTINCT o.SHIP) as cnt
FROM CLASSES AS c
JOIN SHIPS as s on c.CLASS=s.CLASS
LEFT JOIN OUTCOMES as o on s.NAME=o.SHIP and o.RESULT='sunk'
GROUP BY c.CLASS



--a) v
SELECT class, COUNT(ship)
FROM Ships
LEFT JOIN Outcomes
ON Ships.name = Outcomes.ship
AND result = 'sunk'
GROUP BY class;