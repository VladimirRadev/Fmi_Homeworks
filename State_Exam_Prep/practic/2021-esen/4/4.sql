USE movies;

--4.1)
--а) x 
	--incolor!= 'y' ( nie iskame da y)

--б) x 
	--така ще вземем цветните филми с неизвестни дължини
--в) v
SELECT studioName
FROM Movie
WHERE inColor = 'Y'
INTERSECT
SELECT studioName
FROM Movie
WHERE length IS NULL


-- така ще вземем хем тези които имат цветен филм , хем и поне един филм с неизвестна дължина
	-- не задължително същия , точно това което ни се иска в условието

--г) x
	--така може да вземем студио което няма дори мовие,
		--и там е ИЛИ в where , т.е взима или цветните или тези без дължина , но и не двете едновременно


--4.2)
--a) x // v having bool statement
--б) v
SELECT name, COUNT(title)
FROM MovieStar
LEFT JOIN StarsIn ON name = starName
LEFT JOIN Movie
ON movieTitle = title
AND movieYear = year
AND inColor = 'N'
WHERE gender = 'F'
GROUP BY name;

--в) x // v having bool statement
--г) x // ne vzimame tezi aktrisi koito ne sa uchastvali v nito edin film , 
	     --zashtoto tablicata starstin sudurja samo aktiori koito sa uchastvali vuv pone edin film inache nqmashe da gi ima v neq


