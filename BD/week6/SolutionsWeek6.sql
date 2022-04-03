--I.1--
SELECT  m.TITLE,m.YEAR,m.LENGTH
FROM MOVIE m
WHERE (m.LENGTH > 120 or m.LENGTH is null)
and m.YEAR < 2000

--I.2--
SELECT ms.NAME,ms.GENDER
FROM MOVIESTAR ms
WHERE ms.NAME LIKE 'J%' AND YEAR(ms.BIRTHDATE)>=1948
order by ms.NAME DESC

--I.3--
SELECT DISTINCT s.NAME,COUNT( DISTINCT si.STARNAME) as nums
FROM STUDIO s LEFT JOIN MOVIE m on s.NAME=m.STUDIONAME
LEFT JOIN STARSIN si on m.TITLE=si.MOVIETITLE
WHERE m.TITLE is not null and si.MOVIETITLE is not null
GROUP BY s.NAME

--I.4--
SELECT si.STARNAME, COUNT(si.MOVIETITLE) as films
FROM STARSIN si
GROUP BY si.STARNAME

--I.5--
SELECT m.STUDIONAME, m.TITLE,m.YEAR
FROM MOVIE m
WHERE m.YEAR >= ALL (SELECT m1.YEAR FROM MOVIE m1 WHERE m1.STUDIONAME=m.STUDIONAME)
order by m.STUDIONAME DESC

--I.6--
SELECT m.NAME
FROM MOVIESTAR m
WHERE m.GENDER='M' and m.BIRTHDATE >= ALL( Select m1.BIRTHDATE FROM MOVIESTAR m1 WHERE m1.GENDER='M')

--I.7--
SELECT m.STUDIONAME,si.STARNAME,COUNT(si.MOVIETITLE) as films
FROM MOVIE m JOIN STARSIN si on m.TITLE=si.MOVIETITLE
GROUP BY m.STUDIONAME,si.STARNAME
HAVING COUNT(si.MOVIETITLE) >= ALL (SELECT COUNT(si.MOVIETITLE) as films
FROM MOVIE m JOIN STARSIN si on m.TITLE=si.MOVIETITLE
GROUP BY m.STUDIONAME,si.STARNAME)


--I.8--
SELECT si.MOVIETITLE,si.MOVIEYEAR,COUNT (si.STARNAME) 
FROM STARSIN si	
GROUP BY si.MOVIETITLE,si.MOVIEYEAR
HAVING (SELECT COUNT(si1.STARNAME) FROM STARSIN si1 WHERE si1.MOVIETITLE=si.MOVIETITLE GROUP BY si1.MOVIETITLE) >2


--II.1--
SELECT DISTINCT ou.SHIP
FROM OUTCOMES ou
WHERE ou.SHIP LIKE 'C%' or ou.SHIP LIKE 'K%'

--II.2--
SELECT distinct sh.NAME,cl.COUNTRY
FROM CLASSES cl JOIN SHIPS sh on cl.CLASS=sh.CLASS
LEFT JOIN OUTCOMES ou on sh.NAME=ou.SHIP
WHERE ou.SHIP is null or ou.SHIP NOT IN (SELECT ou1.SHIP FROM OUTCOMES ou1 WHERE ou1.RESULT='sunk')


--II.3--
SELECT  cl.COUNTRY,COUNT(distinct ou.SHIP) as num_ships
FROM CLASSES cl LEFT JOIN SHIPS sh on cl.CLASS=sh.CLASS
LEFT JOIN OUTCOMES ou on sh.NAME=ou.SHIP and ou.RESULT='sunk'
GROUP BY cl.COUNTRY


--II.4--
SELECT ou.BATTLE
FROM OUTCOMES ou
GROUP BY ou.BATTLE
HAVING COUNT(ou.SHIP) > (SELECT COUNT(ou1.SHIP) 
FROM OUTCOMES ou1 
WHERE ou1.BATTLE='Guadalcanal'
GROUP BY ou1.BATTLE
)

--II.5--
SELECT ou1.BATTLE as battle
FROM OUTCOMES ou1
GROUP BY ou1.BATTLE
HAVING 
(SELECT COUNT(distinct cl.COUNTRY)
FROM (SELECT ou2.SHIP FROM OUTCOMES ou2 
Where ou1.BATTLE=ou2.BATTLE) as shipsAll LEFT JOIN SHIPS sh on shipsALL.SHIP=sh.NAME
LEFT JOIN CLASSES cl on sh.CLASS=cl.CLASS)  >

(SELECT COUNT(distinct cl.COUNTRY)
FROM (SELECT ou.SHIP
FROM OUTCOMES ou 
WHERE ou.BATTLE='Surigao Strait' ) as ships_at_surgio LEFT JOIN SHIPS sh on ships_at_surgio.SHIP=sh.NAME
LEFT JOIN CLASSES cl on sh.CLASS=cl.CLASS)

--II.6--
SELECT *
FROM (SELECT sh.NAME,cl.DISPLACEMENT,cl.NUMGUNS
FROM CLASSES cl  JOIN SHIPS sh on cl.CLASS=sh.CLASS
WHERE cl.DISPLACEMENT <= ALL (SELECT cl2.DISPLACEMENT FROM CLASSES cl2) ) as lightest_ships
WHERE lightest_ships.NUMGUNS >= ALL ((SELECT cl.NUMGUNS
FROM CLASSES cl  JOIN SHIPS sh on cl.CLASS=sh.CLASS
WHERE cl.DISPLACEMENT <= ALL (SELECT cl2.DISPLACEMENT FROM CLASSES cl2) ))

--II.7--
SELECT COUNT(ok_ships_and_battle_date.SHIP) as repaired_then_win
FROM
(SELECT ou.SHIP,b.DATE
FROM OUTCOMES ou LEFT JOIN BATTLES b on ou.BATTLE=b.NAME
WHERE ou.RESULT='ok') as ok_ships_and_battle_date LEFT JOIN 
(SELECT ou.SHIP,b.DATE
FROM OUTCOMES ou LEFT JOIN BATTLES b on ou.BATTLE=b.NAME
WHERE OU.RESULT='damaged') as damaged_ships_and_battle_date
on ok_ships_and_battle_date.SHIP=damaged_ships_and_battle_date.SHIP
WHERE ok_ships_and_battle_date.DATE > damaged_ships_and_battle_date.DATE
GROUP BY ok_ships_and_battle_date.SHIP

--II.8--
SELECT distinct ok_ships_and_battle_date.SHIP
FROM
(SELECT ou.SHIP,b.DATE,b.NAME
FROM OUTCOMES ou LEFT JOIN BATTLES b on ou.BATTLE=b.NAME
WHERE ou.RESULT='ok') as ok_ships_and_battle_date LEFT JOIN 
(SELECT ou.SHIP,b.DATE,b.NAME
FROM OUTCOMES ou LEFT JOIN BATTLES b on ou.BATTLE=b.NAME
WHERE OU.RESULT='damaged') as damaged_ships_and_battle_date
on ok_ships_and_battle_date.SHIP=damaged_ships_and_battle_date.SHIP
WHERE ok_ships_and_battle_date.DATE > damaged_ships_and_battle_date.DATE
and          (SELECT COUNT(distinct ou.SHIP)
					FROM OUTCOMES ou
					WHERE ou.BATTLE=ok_ships_and_battle_date.NAME
					GROUP BY ou.BATTLE) > 
                          (SELECT COUNT(distinct ou.SHIP)
								FROM OUTCOMES ou
								WHERE ou.BATTLE=damaged_ships_and_battle_date.NAME
								GROUP BY ou.BATTLE
								)


--III.1--
SELECT l.model,l.code,l.screen
FROM laptop l
WHERE l.screen=11 or l.screen=15

--III.2--
SELECT distinct pr2.model
FROM pc pC LEFT JOIN product pr2 on pC.model=pr2.model
WHERE pC.price < (SELECT l.price
FROM laptop l LEFT JOIN product pr on l.model=pr.model
WHERE l.price <= ALL (SELECT l1.price FROM laptop l1 LEFT JOIN product pr1 on l1.model=pr1.model
WHERE pr1.maker=pr.maker) and pr2.maker=pr.maker)

--III.3--
SELECT p.model, AVG(p.price) as avg_price
FROM pc p LEFT JOIN product pr on p.model=pr.model
GROUP BY p.model,pr.maker
HAVING AVG (p.price) < (SELECT MIN(l.price) 
FROM laptop l LEFT JOIN product pr1 on l.model=pr1.model
WHERE l.price <= ALL(SELECT l.price FROM laptop l left join product pr2 on l.model=pr2.model
WHERE pr2.model=pr1.model) and pr1.maker=pr.maker)


--III.4--
SELECT p.code,pr.maker,(SELECT COUNT(*)
FROM pc p1 
WHERE p1.model = p.model
and p1.price >= p.price) as more_expensive
FROM pc p LEFT JOIN product pr on p.model=pr.model







