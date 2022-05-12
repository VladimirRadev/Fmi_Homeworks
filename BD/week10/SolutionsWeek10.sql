--II.a--

ALTER TABLE Airplane
DROP COLUMN code 


ALTER TABLE Airplane
ADD code  VARCHAR(50) NOT NULL;

ALTER TABLE Airplane
ADD CONSTRAINT pk_airplane PRIMARY KEY(code)

----
ALTER TABLE Agency
DROP COLUMN name 


ALTER TABLE Agency
ADD name  VARCHAR(50) NOT NULL;

ALTER TABLE Agency
ADD CONSTRAINT pk_agency PRIMARY KEY(name)


----
ALTER TABLE CUSTOMER
DROP COLUMN id 


ALTER TABLE Customer
ADD id  INT  NOT NULL;

ALTER TABLE Customer
ADD CONSTRAINT pk_customer PRIMARY KEY(id)




----
ALTER TABLE Airport
DROP COLUMN code 


ALTER TABLE Airport
ADD code  VARCHAR(50) NOT NULL

ALTER TABLE Airport
ADD CONSTRAINT pk_airport PRIMARY KEY(code)


----
ALTER TABLE Flight
DROP COLUMN fnumber 


ALTER TABLE Flight
ADD fnumber VARCHAR(50) NOT NULL

ALTER TABLE Flight
ADD CONSTRAINT pk_flight PRIMARY KEY(fnumber)



----
ALTER TABLE Booking
DROP COLUMN code 


ALTER TABLE Booking
ADD code VARCHAR(50) NOT NULL

ALTER TABLE Booking
ADD CONSTRAINT pk_booking PRIMARY KEY(code)


--II.b--

ALTER TABLE Flight
ADD CONSTRAINT fk_flight_to_airline foreign key(airline_operator)
REFERENCES Airlane(code)

ALTER TABLE Booking
ADD Constraint fk_booking_to_airline foreign key(airline_code)
REFERENCES Airlane(code)


ALTER TABLE Flight
ADD CONSTRAINT fk_flight_dep_airport_to_airport foreign key(dep_airport)
REFERENCES Airport(code)

ALTER TABLE Flight
ADD CONSTRAINT fk_flight_arr_airport_to_airport foreign key(arr_airport)
REFERENCES Airport(code)

--StignalSum do : kod na samoleta ot relaciqta flight trqbva da sushetsvuva w relaciqta airplane