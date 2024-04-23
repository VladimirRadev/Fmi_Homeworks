USE ships;


-- esen 2014 zad.6.1

--moe resh

--Pomoshtni:
SELECT distinct sh.LAUNCHED, sh.NAME
FROM SHIPS as sh
ORDER BY SH.LAUNCHED

SELECT YEAR(DATE)
FROM OUTCOMES
JOIN BATTLES on BATTLE=NAME

--KRAINO:
SELECT NAME
FROM SHIPS
WHERE LAUNCHED IN (SELECT YEAR(DATE)
				     FROM OUTCOMES
					 JOIN BATTLES on BATTLE=NAME)

--a) x, syntax error where i agregatna funciq v nego
--b) v
--SELECT distinct SHIPS.NAME 
--FROM BATTLES,SHIPS
--WHERE LAUNCHED = YEAR(DATE)
--c) x, selectva ime na bitka , a nie iskame ime na korab
--d) x, syntax error , join on kluch a ne statement 

-- esen 2014 zad.6.2

--moe resh
SELECT cl.COUNTRY, COUNT(o.SHIP) AS SUNK_CNT
FROM CLASSES as cl
LEFT JOIN SHIPS as sh on cl.CLASS=sh.CLASS
LEFT JOIN OUTCOMES as o on sh.NAME = o.SHIP
WHERE (o.RESULT='sunk' OR o.RESULT is null) and cl.COUNTRY IN
							(SELECT cl.COUNTRY
							FROM CLASSES as cl
							LEFT JOIN SHIPS as sh on cl.CLASS=sh.CLASS
							GROUP BY cl.COUNTRY
							HAVING COUNT(sh.NAME) <= 3 )
GROUP BY cl.COUNTRY;



--a) x, syntax error, tables are named with alias but aren't used
--b) x ,syntax error, count (result is sunk) isn't allowed in an aggregate function
--c) x , syntax error, alias are assigned but unused later, 'sunk'
--d) x , syntax error, where and aggregate function
--e) v
--SELECT distinct country,(
--						select count(*)
--						from classes c2 join ships s on c2.CLASS=s.CLASS
--						join OUTCOMES o on s.NAME=o.SHIP
--						where c2.COUNTRY=c.COUNTRY and result = 'sunk')
--FROM CLASSES c
--where (select count(*)
--		from classes c2  join ships s on c2.CLASS=s.CLASS
--		where c2.COUNTRY=c.COUNTRY) <= 3 