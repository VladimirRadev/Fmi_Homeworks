USE ships;


--lqto/2010 zad 2.1 


SELECT *
FROM CLASSES

--a) x
--SELECT *
--FROM CLASSES c1
--INNER JOIN CLASSES c2 on c1.CLASS=c2.CLASS
--WHERE c1.NUMGUNS < 6 AND c2.NUMGUNS > 10   // joinvash abs sushtite elementi , shte izvede prazno

--b) x
--SELECT DISTINCT COUNTRY
--FROM CLASSES
--WHERE NUMGUNS < 6 AND NUMGUNS > 10 // pak vrushta prazno

--c) v
--SELECT DISTINCT COUNTRY
--FROM CLASSES
--WHERE NUMGUNS > 10 AND COUNTRY IN
--									(SELECT COUNTRY
--									FROM CLASSES
--									WHERE NUMGUNS<6)

--d) x
--SELECT COUNTRY
--FROM CLASSES
--WHERE NUMGUNS > 10
--UNION //trqbva da e intersect za da e vqrno
--SELECT COUNTRY
--FROM CLASSES
--WHERE NUMGUNS < 6  //dava ni durjavi koito moje da imat samo >10 ili samo <6 , no ne ednovremnno i dvete



--lqto/2010 zad 2.1 

--a) x //samo join , a ne left/right join , ne hvashta countries bez korab
--b) x //samo join , a ne left/right join + sintaktichna wgrehska "where agregatna funkciq"
--c) v
--SELECT DISTINCT c.COUNTRY,COUNT(o.BATTLE) as CNT_BTLS
--FROM CLASSES as c
--LEFT JOIN SHIPS as s on c.CLASS=s.CLASS
--LEFT JOIN OUTCOMES as o on s.NAME=o.SHIP
--GROUP BY c.COUNTRY
--HAVING COUNT(o.BATTLE) <= 3


--SELECT *
--FROM CLASSES as c
--LEFT JOIN SHIPS as s on c.CLASS=s.CLASS
--LEFT JOIN OUTCOMES as o on s.NAME=o.SHIP

--d) x // pak samo join a ne left/right join , ne hvashtame cases
