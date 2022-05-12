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
	CONSTRAINT pk_location_combination UNIQUE(sector,row,position)
);

CREATE TABLE ITEM(
	code CHAR(10) NOT NULL CONSTRAINT pk_item PRIMARY KEY,
	manufacturer_code CHAR(10) NOT NULL CONSTRAINT fk_item_to_manufacturer FOREIGN KEY 
	REFERENCES MANUFACTURER(code),
	type VARCHAR(50) NOT NULL,
	loc_code VARCHAR(20) NOT NULL CONSTRAINT fk_item_to_location FOREIGN KEY 
	REFERENCES LOCATION(code)
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
		


select *
from MANUFACTURER

--ALTER TABLE MOVIE
--ADD CONSTRAINT uk_title_year UNIQUE(title,year)


--CONSTRAINT [constraint_name] UNIQUE(id,lastname,..)
