USE master
GO
if exists (select * from sysdatabases where name='warehouse')
	DROP DATABASE warehouse
GO

CREATE DATABASE warehouse
GO
USE warehouse
GO

----- Create Tables -----
CREATE TABLE MANUFACTURER(
	code CHAR(10) NOT NULL CONSTRAINT pk_manufacturer PRIMARY KEY,
	name VARCHAR(50) NOT NULL,
	county VARCHAR(50) NOT NULL,
	year CHAR(4) NOT NULL
);

CREATE TABLE LOCATION(
	code VARCHAR(20) NOT NULL CONSTRAINT pk_location_code PRIMARY KEY,
	sector CHAR(1) NOT NULL,
	row INT NOT NULL,
	position INT NOT NULL,
	CONSTRAINT pk_location_combination UNIQUE(sector,row,position),
	CHECK (code like 'S%R%P%')
);

CREATE TABLE ITEM(
	code CHAR(10) NOT NULL CONSTRAINT pk_item PRIMARY KEY,
	manufacturer_code CHAR(10) NOT NULL CONSTRAINT fk_item_to_manufacturer FOREIGN KEY 
	REFERENCES MANUFACTURER(code) ,
	type VARCHAR(50) NOT NULL, 
	loc_code VARCHAR(20) NOT NULL UNIQUE CONSTRAINT fk_item_to_location FOREIGN KEY 
	REFERENCES LOCATION(code),
	CHECK (type in ('Sofa','Chair','Table'))
);
CREATE TABLE SOFA(
	basematerial VARCHAR(50) NOT NULL,
	price DECIMAL(10,2) NOT NULL,
	item_code CHAR(10) NOT NULL UNIQUE CONSTRAINT fk_sofa_to_item FOREIGN KEY REFERENCES ITEM(code),
	weight DECIMAL(10,2) NOT NULL,
	cover_colour VARCHAR(50),
	num_seats INT NOT NULL
	CHECK (num_seats >= 1)
);

CREATE TABLE CHAIR(
	basematerial VARCHAR(50) NOT NULL,
	price DECIMAL(10,2) NOT NULL,
	item_code CHAR(10) NOT NULL UNIQUE CONSTRAINT fk_chair_to_item FOREIGN KEY REFERENCES ITEM(code),
	colour VARCHAR(50) NOT NULL,
	num_legs INT
	CHECK (num_legs in (3,4) OR num_legs is null)
);

CREATE TABLE TABLE_(
	basematerial VARCHAR(50) NOT NULL,
	price DECIMAL(10,2) NOT NULL,
	item_code CHAR(10) NOT NULL UNIQUE CONSTRAINT fk_table_to_item FOREIGN KEY REFERENCES ITEM(code),
	type VARCHAR(11) NOT NULL
	CHECK (type IN ('extendable','dining','oval'))
);

CREATE TABLE BUNDLE(
	id INT NOT NULL CONSTRAINT pk_bundle PRIMARY KEY,
	name VARCHAR(20) NOT NULL,
	description VARCHAR(100)
);

CREATE TABLE BUNDLEITEM(
	bundle_id INT NOT NULL CONSTRAINT fk_bundleitem_to_bundle FOREIGN KEY
	REFERENCES BUNDLE(id),
	item_code CHAR(10) NOT NULL CONSTRAINT fk_bundleitem_to_item FOREIGN KEY
	REFERENCES ITEM(code)
);

CREATE TABLE STORE(
	code VARCHAR(20) NOT NULL CONSTRAINT pk_store PRIMARY KEY,
	name VARCHAR(50) NOT NULL,
	address VARCHAR(50) NOT NULL,
	type VARCHAR(20) NOT NULL
	CHECK (type IN ('department store','furniture store','cake shop'))
);


CREATE TABLE DELIVERY_FEATURE(
	id INT NOT NULL CONSTRAINT pk_delivery_feature PRIMARY KEY,
	delivery_company VARCHAR(20) NOT NULL,
	delivery_vehicle VARCHAR(20) NOT NULL,
	CHECK (delivery_company IN ('DHL','EKONT','SPEEDY') AND delivery_vehicle IN ('Van','Mini Truck','Truck')),
	CONSTRAINT uq_delivery_feature_combination UNIQUE(delivery_company,delivery_vehicle)
);

CREATE TABLE DELIVERY(
	code CHAR(10) NOT NULL CONSTRAINT pk_delivery PRIMARY KEY,
	bundle_id INT NOT NULL CONSTRAINT fk_delivery_to_bundle FOREIGN KEY 
	REFERENCES BUNDLE(id),
	store_code VARCHAR(20) NOT NULL,
	delivery_feature_id INT NOT NULL CONSTRAINT fk_delivery_to_delivery_feature FOREIGN KEY 
	REFERENCES DELIVERY_FEATURE(id),
	export_date DATE NOT NULL,
	delivery_date DATE NOT NULL,
	CONSTRAINT fk_delivery_to_store FOREIGN KEY(store_code)
	REFERENCES STORE(code),
	CHECK (export_date <= delivery_date)
);


------- Insert data ------------
INSERT INTO MANUFACTURER
VALUES('6db4od3p68','Qvor','Bulgaria','1992'),
		('x5hbimdoph','Zora','Bulgaria','2001'),
		('mhozm5dw0d','Koritarov','Bulgaria','1980'),
		('qnpmyzn1ng','Kedur','Bulgaria','1998'),
		('23yw7nc7j5','Progres','Bulgaria','2008'),
		('e93izv7om3','Green Furniture Concept','Sweden','1978'),
		('7w5cd2rivc','Noremax','Norway','2019'),
		('4ixnhov07f','Wood factory Germany','Germany','2008'),
		('9y02x1k9jb','AviNordic','Norway','2007'),
		('nfrkgziiwn','P&M furniture','Romania','1989')

		
INSERT INTO LOCATION
VALUES ('SAR22P1','A',22,1),
		('SAR22P12','A',22,12),
		('SBR3P5','B',3,5),
		('SCR3P1','C',3,1),
		('SBR3P4','B',3,4),
		('SDR42P9','D',42,9),
		('SZR6P1','Z',6,1),
		('SWR5P2','W',5,2),
		('SWR2P2','W',2,2),
		('SBR3P9','B',3,9),
		('SCR3P21','C',3,21),
		('SBR13P4','B',13,4),
		('SDR2P9','D',2,9),
		('SZR56P1','Z',56,1),
		('SWR3P2','W',3,2),
		('SWR6P1','W',6,1),
		('SRR4P2','R',4,2)

		
INSERT INTO ITEM
	VALUES ('7z4u1wxWDM','23yw7nc7j5','Sofa','SAR22P1'),
	('vzN9UJ27Rx','23yw7nc7j5','Sofa','SAR22P12'),
	('I80VAvwP4W','x5hbimdoph','Chair','SBR3P5'),
	('Frgk1OlOrE','6db4od3p68','Sofa','SCR3P1'),
	('EAavlpQpF6','e93izv7om3','Chair','SBR3P4'),
	('6mC5Hvwmo6','x5hbimdoph','Chair','SDR42P9'),
	('vEVHOYogtZ','6db4od3p68','Sofa','SZR6P1'),
	('J2CB4qX7by','9y02x1k9jb','Chair','SWR5P2'),
	('PPi4acu83n','23yw7nc7j5','Chair','SWR2P2'),
	('BaQTZkmAWf','9y02x1k9jb','Chair','SBR3P9'),
	('fSdg9dEzaX','mhozm5dw0d','Table','SCR3P21'),
	('ZvCfjJlha2','9y02x1k9jb','Sofa','SBR13P4'),
	('92oI7HReFW','x5hbimdoph','Table','SDR2P9'),
	('CzfhY1iZJo','e93izv7om3','Sofa','SZR56P1'),
	('pXM84Qs0UZ','mhozm5dw0d','Table','SWR3P2')





INSERT INTO SOFA
VALUES ('Leather',239.99,'7z4u1wxWDM',29.5,'Lemon',2),
('Leather',122,'CzfhY1iZJo',15,'Forest',1),
('Polyester',99.99,'Frgk1OlOrE',14.5,'Brown',1),
('Linen',659.99,'vEVHOYogtZ',39.8,'Gold',6),
('Woolen',445.99,'vzN9UJ27Rx',25.2,'Red',5),
('Polyester',139,'ZvCfjJlha2',19,'Lemon',4)

INSERT INTO CHAIR
VALUES ('Leather',256.99,'6mC5Hvwmo6','Gold',4),
('Vinyl',45,'BaQTZkmAWf','Red',4),
('Fabric',69.99,'EAavlpQpF6','Yellow',3),
('Fabric',89.99,'I80VAvwP4W','Grey',3),
('Mesh',300,'J2CB4qX7by','Red',4),
('Mesh',249,'PPi4acu83n','Black',4)


INSERT INTO TABLE_
VALUES ('Solid wood',240,'92oI7HReFW','dining'),
('Wood',56,'fSdg9dEzaX','extendable'),
('Butcher block',69.99,'pXM84Qs0UZ','oval')



INSERT INTO BUNDLE(id,name)
VALUES (1,'bulgarian_chairs'),
		(4,'sweden_sofas'),
		(7,'norway_sofas'),
		(8,'bulgarian_tables')
INSERT INTO BUNDLE
VALUES (2,'norway_bundle','It contains all types of furniture created in Norway'),
		(3, 'three_legged_chairs','All three legged chairs'),
		(5,'bulgarian_bundle','It contains all types of furniture created in Bulgaria'),
		(6,'sweden_bundle','It contains all types of furniture created in Sweden'),
		(9,'all_in','It contains all furniture stored in the warehouse')	


INSERT INTO BUNDLEITEM
VALUES (1,'6mC5Hvwmo6'),
		(1,'BaQTZkmAWf'),
		(1,'EAavlpQpF6'),
		(1,'I80VAvwP4W'),
		(1,'J2CB4qX7by'),
		(1,'PPi4acu83n'),
		(2,'BaQTZkmAWf'),
		(2,'J2CB4qX7by'),
		(2,'ZvCfjJlha2'),
		(3,'EAavlpQpF6'),
		(3,'I80VAvwP4W'),
		(4,'CzfhY1iZJo'),
		(5,'fSdg9dEzaX'),
		(5,'pXM84Qs0UZ'),
		(5,'7z4u1wxWDM'),
		(5,'PPi4acu83n'),
		(5,'vzN9UJ27Rx'),
	    (5,'Frgk1OlOrE'),
		(5,'vEVHOYogtZ'),
		(5,'6mC5Hvwmo6'),
		(5,'92oI7HReFW'),
		(5,'I80VAvwP4W'),
		(6,'CzfhY1iZJo'),
		(6,'EAavlpQpF6'),
		(8,'fSdg9dEzaX'),
		(8,'pXM84Qs0UZ'),
		(8,'92oI7HReFW')
		


INSERT INTO STORE
VALUES ('VID_EOOD','Mebeli Videnov','Sofia ul.stradjanka 57','furniture store'),
('ZOR_ED','Zora','Sofia ul.Elisaveta Bagrqna','furniture store'),
('MOS_AD','Mall of sofia','Sofia al.stamboliyski','department store'),
('NED_OOD','Sladkarnica Nedelq','Sofia manastirski livadi - zapad','cake shop')

INSERT INTO DELIVERY_FEATURE
VALUES (1,'DHL','VAN'),
		(2,'DHL','Truck'),
		(3,'SPEEDY','VAN'),
		(4,'EKONT','Mini truck')

INSERT INTO DELIVERY
VALUES ('MvlbUA0tO3',3,'NED_OOD',1,'2022-05-12','2022-05-13'),
	('pr9HILbFSL',8,'VID_EOOD',4,'2022-04-23','2022-05-1'),
	('oKhYVT8jJl',5,'VID_EOOD',2,'2020-09-12','2020-09-25'),
	('TQuO36i30j',4,'MOS_AD',4,'2021-06-26','2022-07-08'),
	('c7vUCF0Ms5',6,'ZOR_ED',3,'2020-01-12','2020-01-13'),
	('jg5Wj9Caah',2,'ZOR_ED',3,'2020-02-12','2022-02-13')


	/*
	
	!!! S ctrl + a na celiq dokument i posle execute suzdava kakto bazata danni taka i vscihkite
	tablici taka i gi pulni s informaciq 


	PRIMERNI ZAQVKI :

	1)
	SELECT s.address
	FROM DELIVERY d left join DELIVERY_FEATURE df on d.delivery_feature_id=df.id LEFT JOIN
	STORE s on d.store_code=s.code
	WHERE df.delivery_vehicle='Van' and s.type='cake shop'

	^Namerete adresite na vsichki sladkarnici koito sa poluchili  pratka ot van

	2) SELECT distinct b.id,i.type,m.county
	FROM BUNDLE b LEFT JOIN BUNDLEITEM bi on b.id=bi.bundle_id LEFT JOIN
	ITEM i on bi.item_code=i.code LEFT JOIN MANUFACTURER m ON i.manufacturer_code=m.code
	WHERE b.id=2

	 ^ Namerete tiput na produkta(table | sofa | chair) i durjavata v koqto e proizveden
	Vseki produkt ot bundle s id 2

	3)
	select MANUFACTURER.name,MANUFACTURER.county,ITEM.code,ITEM.type
	from MANUFACTURER join ITEM on MANUFACTURER.code=ITEM.manufacturer_code 
	ORDER BY MANUFACTURER.name

	 ^ Vsichki itemi v sklada kato za vseki item imame ime na proizvoditel , durjava na proizvoditel,
	 code na itema i tip na itema

	 --------------------------------------
 imeto na table e table_ zashtoto table e specialna duma i ne moje da e ime na tablica !!!

 ako vi se zanimava moje da slojete i ogranichenie za referentna cqlost tam ON DELETE .. 
 I ON UPDATE .. NA FOREIGN KLUCHOVETE:

 primer: 
 CREATE TABLE ITEM(
	code CHAR(10) NOT NULL CONSTRAINT pk_item PRIMARY KEY,
	manufacturer_code CHAR(10) NOT NULL CONSTRAINT fk_item_to_manufacturer FOREIGN KEY 
	REFERENCES MANUFACTURER(code) ------> ON UPDATE CASCADE  <-------- ,
	type VARCHAR(50) NOT NULL, 
	loc_code VARCHAR(20) NOT NULL UNIQUE CONSTRAINT fk_item_to_location FOREIGN KEY 
	REFERENCES LOCATION(code),
	CHECK (type in ('Sofa','Chair','Table'))
);
*/


