--I.1--
INSERT INTO MOVIESTAR(NAME,BIRTHDATE)
values ('Nicole Kidman','1967-06-20')

--I.2--
DELETE FROM MOVIEEXEC
WHERE CERT#  in (
select me.CERT# 
FROM MOVIEEXEC me
WHERE me.NETWORTH < 30000000)

--I.3--
DELETE FROM MOVIESTAR
WHERE NAME in (SELECT ms.NAME FROM MOVIESTAR ms where ms.ADDRESS is null)


--II.4--
INSERT INTO product(maker,model,type)
VALUES ('C','1100','PC')

INSERT INTO pc VALUES (12,'1100',2400,2048,500,'52x',299)


--II.5--
DELETE FROM pc 
WHERE model='1100'

DELETE FROM product
where model='1100'


--II.6--
DELETE FROM laptop
WHERE code in
(
SELECT lap.code
FROM 
(SELECT *
FROM product prr
WHERE prr.type='Laptop'
AND prr.maker in
(SELECT distinct pr.maker
FROM product pr
WHERE pr.type='Laptop' and pr.maker NOT IN (select distinct pr1.maker from product pr1 where pr1.type='Printer') )) as toDel LEFT JOIN laptop lap 
on toDel.model=lap.model )

--II.7--
UPDATE product
SET maker='A'
where maker='B'

--II.8--
UPDATE pc
SET price=price/2,hd+=20

UPDATE product
SET maker='B'
where model='1298'


--II.9--
UPDATE laptop
SET screen-=1
where code in
(select lap.code
from product pr JOIN laptop lap on pr.model=lap.model
where pr.maker='B')


--III.10--
INSERT INTO CLASSES
values ('Nelson','bb','Gt.Britain',9,16,34000)

INSERT INTO SHIPS(NAME,CLASS,LAUNCHED)
VALUES('Nelson','Nelson',1927)

INSERT INTO SHIPS ( NAME,CLASS,LAUNCHED)
VALUES('Rodney','Nelson',1927)


--III.11--
DELETE FROM SHIPS
where NAME in (
SELECT distinct sh.NAME
FROM SHIPS sh JOIN OUTCOMES ou on sh.NAME=ou.SHIP
WHERE ou.RESULT='sunk' ) 


--III.12--
UPDATE CLASSES
SET BORE*=2.5,
DISPLACEMENT/=1.1





