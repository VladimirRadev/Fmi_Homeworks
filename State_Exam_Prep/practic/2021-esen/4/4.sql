USE movies;

--4.1)
--�) x 
	--incolor!= 'y' ( nie iskame da y)

--�) x 
	--���� �� ������ �������� ����� � ���������� �������
--�) v
SELECT studioName
FROM Movie
WHERE inColor = 'Y'
INTERSECT
SELECT studioName
FROM Movie
WHERE length IS NULL


-- ���� �� ������ ��� ���� ����� ���� ������ ���� , ��� � ���� ���� ���� � ���������� �������
	-- �� ������������ ����� , ����� ���� ����� �� �� ���� � ���������

--�) x
	--���� ���� �� ������ ������ ����� ���� ���� �����,
		--� ��� � ��� � where , �.� ����� ��� �������� ��� ���� ��� ������� , �� � �� ����� ������������


--4.2)
--a) x // v having bool statement
--�) v
SELECT name, COUNT(title)
FROM MovieStar
LEFT JOIN StarsIn ON name = starName
LEFT JOIN Movie
ON movieTitle = title
AND movieYear = year
AND inColor = 'N'
WHERE gender = 'F'
GROUP BY name;

--�) x // v having bool statement
--�) x // ne vzimame tezi aktrisi koito ne sa uchastvali v nito edin film , 
	     --zashtoto tablicata starstin sudurja samo aktiori koito sa uchastvali vuv pone edin film inache nqmashe da gi ima v neq


