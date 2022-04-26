--I.a--
CREATE TABLE Product(
maker CHAR(1),
model CHAR(4),
type VARCHAR(7)
);

CREATE TABLE Printer(
code INTEGER,
model CHAR(4),
price DECIMAL(8,2)
);

--I.b--
INSERT INTO Product(maker,model,type)
VALUES('B','1269','Printer')

INSERT INTO Product(maker,model,type)
VALUES('A','1169','PC')

INSERT INTO Printer(code,model,price)
values(2,'1269',434.55)


INSERT INTO Printer(code,model,price)
values(1,'1169',699)

--I.v--
ALTER TABLE Printer ADD type_ VARCHAR(6);
ALTER TABLE Printer	ADD color CHAR(1) DEFAULT 'n';

--I.g--
ALTER TABLE Printer Drop column price;

--I.d--
DROP TABLE Printer;
DROP TABLE Product;


--II.a--
CREATE TABLE Users(
id INTEGER UNIQUE NOT NULL,
email VARCHAR(20) NOT NULL,
password VARCHAR(20) NOT NULL,
registration_date DATETIME NOT NULL
);

CREATE TABLE Friends(
lhs_Id INTEGER NOT NULL,
rhs_Id INTEGER NOT NULL
);

CREATE TABLE Walls(
sender_Id INTEGER NOT NULL,
receiver_Id INTEGER NOT NULL,
message VARCHAR(255) NOT NULL,
date DATETIME NOT NULL
);

CREATE TABLE Groups(
	id INTEGER UNIQUE NOT NULL,
	name VARCHAR(20) NOT NULL,
	description VARCHAR (255) DEFAULT ''
);

CREATE TABLE GroupMembers(
	group_id INTEGER NOT NULL,
	user_id INTEGER NOT NULL
);




--II.b--

insert into Users(id,email,password,registration_date)
values(1,'ss@ss.bg','kur12',GETDATE())

insert into Users(id,email,password,registration_date)
values(2,'bgMama@abv.bg','malkapishka',GETDATE())

insert into Users(id,email,password,registration_date)
values(3,'bgMa@abv.bg','malishka',GETDATE())

INSERT INTO Friends(lhs_Id,rhs_Id)
VALUES(1,2)

INSERT INTO Walls(sender_Id,receiver_Id,message,date)
values (1,2,'ZNaeshhh. Dali veee',GETDATE())

INSERT INTO Groups(id,name)
VALUES(1,'POD_PRIKRITIE')

INSERT INTO Groups(id,name,description)
VALUES(2,'shkembe','Homesexual Stuffs')

INSERT INTO GroupMembers(group_id,user_id)
values(1,1)

INSERT INTO GroupMembers(group_id,user_id)
values(1,2)

INSERT INTO GroupMembers(group_id,user_id)
values(2,1)

INSERT INTO GroupMembers(group_id,user_id)
values(2,3)



--EXAMPLE_QUERIES--
SELECT u.id as user_,COUNT(DISTINCT gm.group_id) as total_count_groups
FROM Users u LEFT JOIN GroupMembers gm on u.id=gm.user_id
GROUP BY u.id


SELECT * 
FROM GroupMembers