--I.1--



-- DB Flights
-- 1) Add column num_pass to the table Flight, which will contain the
-- number of passangers that confirmed their reservation for the flight.
alter table Flight add num_pass int check(num_pass>=0);

-- 2) Add a new column num_book to the Agency table, which contains the
-- reservations count to the current agency.
alter table agency add num_book int check(num_book>=0);

-- 3) Create a trigger on the Booking table that executes when inserting a
-- reservation in the table and increases the passengers count that confirmed
-- the reservation in the Flight table and in the respected agency.

-- drop trigger if exists in NO_CONSTR_DB DB
USE NO_CONSTR_DB
GO
if exists (select 1
			 from sys.objects
			where type = 'TR'
			  and name = 'ai_booking_increase_conf_res')
	drop trigger ai_booking_increase_conf_res;
GO

-- create trigger "ai_booking_increase_conf_res"
create trigger ai_booking_increase_conf_res on booking
for insert 
as
update Flight
   set num_pass = isnull(num_pass,0) + (select count(1) from inserted where flight_number = fnumber)
 where fnumber in (select flight_number from inserted)
update Agency
   set num_book = isnull(num_book,0) + (select count(1) from inserted where agency = name)
 where name in (select agency from inserted);

-- several scripts to check the trigger
-- firstly, delete records if they exist in the booking table
delete from booking where code in ('YV298P','YJ298P','YK298P');

-- set to null the num_pass values for fnumber 'SU2061' and 'SU2060'
update Flight
   set num_pass = null
 where fnumber in ('SU2061', 'SU2060');

-- set to null the num_book values for agencies 'Travel Two' and
-- 'Travel Tour'
update Agency
   set num_book = null
 where name in ('Travel Two', 'Travel Tour');

-- insert some booking records
insert into Booking
values('YV298P', 'Travel Two', 'FB', 'SU2061', 3, '2014-10-09', '2014-11-25', 350, 1),
	  ('YJ298P', 'Travel Two', 'FB', 'SU2061', 1, '2014-10-08', '2014-11-25', 350, 1),
	  ('YK298P', 'Travel Tour', 'FB', 'SU2060', 2, '2014-10-07', '2014-11-25', 350, 1);

-- see if anything happened to the Flight table
select f.*
  from Flight f
 where f.fnumber in ('SU2061', 'SU2060');

-- see if anything happened to the Agency table
select a.*
  from Agency a
 where a.name in ('Travel Two', 'Travel Tour');

-- 4) Create a trigger on Booking table that executes on
-- deleting a reservation in the table and decreases the
-- passanger(s) count that confirmed the reservation in the
-- Flight table as well as the reservations count in Agency table
-- (for the respected agency).
USE NO_CONSTR_DB
GO
if exists (select 1
			 from sys.objects
			where type = 'TR'
			  and name = 'ad_booking_decrease_conf_res')
	drop trigger ad_booking_decrease_conf_res;
GO

-- create trigger "ad_booking_decrease_conf_res"
create trigger ad_booking_decrease_conf_res on booking
for delete 
as
update Flight
   set num_pass = num_pass - (select count(1) from deleted where flight_number = fnumber)
 where fnumber in (select flight_number from deleted);
update Agency
   set num_book = num_book - (select count(1) from deleted where agency = name)
 where name in (select agency from deleted);

-- delete some booking records
delete from Booking
 where code in ('YV298P', 'YK298P');

/* Insert the statements, that were deleted, back into Booking
insert into Booking
values('YK298P', 'Travel Tour', 'FB', 'SU2060', 2, '2014-10-07', '2014-11-25', 350, 1),
		('YV298P', 'Travel Two', 'FB', 'SU2061', 3, '2014-10-09', '2014-11-25', 350, 1);
*/

-- see if anything happened to the Flight table
select f.*
  from Flight f
 where f.fnumber in ('SU2061', 'SU2060');

-- see if anything happened to the Agency table
select a.*
  from Agency a
 where a.name in ('Travel Two', 'Travel Tour');

-- 5) Create a trigger for the booking table which executes on update
-- of the reservation in the table and increases/decreases the passengers'
-- count that confirmed the reservation in Flight based on the status column
-- change.
USE NO_CONSTR_DB
GO
if exists (select 1
			 from sys.objects
			where type = 'TR'
			  and name = 'au_booking_incr_decr_conf_res')
	drop trigger au_booking_incr_decr_conf_res;
GO

-- create trigger "au_booking_incr_decr_conf_res"
create trigger au_booking_incr_decr_conf_res on booking
for update 
as
-- for status set from 0 to 1
if exists (select 1
			 from inserted
			where status = 1)
	and exists (select 1
				  from deleted
				 where status = 0)
	begin
		update Flight
		   set num_pass = isnull(num_pass,0) + (select count(1) from inserted where flight_number = fnumber)
		 where fnumber in (select flight_number from inserted);
	end

-- status set from 1 to 0
if exists (select 1
		     from inserted
			where status = 0)
	and exists (select 1
				  from deleted
				 where status = 1)
	begin
		update Flight
		   set num_pass = num_pass - (select count(1) from inserted where flight_number = fnumber)
		 where fnumber in (select flight_number from inserted);
	end;

select *
  from Booking
 where code in ('YV298P', 'YJ298P', 'YK298P');

-- checking trigger
update Booking
   set status = 0
 where code = 'YJ298P';

select f.*
  from Flight f
 where f.fnumber in (select	flight_number from Booking where code = 'YJ298P');

-- Bonus: Create a trigger that logs records for the booking table
-- on every change made on existing records.

-- creating an audit table (copying only table structure, no data)
select * into booking_audit from Booking where 1=2;

-- adding additional columns for change date and user that
-- made the change
alter table booking_audit add udated_by varchar(60), updated_on datetime default getdate(), operation_type varchar(20);

-- drop trigger if exists
USE NO_CONSTR_DB
GO
if exists (select 1
			 from sys.objects
			where type = 'TR'
			  and name = 'aiu_booking_audit')
	drop trigger aiu_booking_audit;
GO

CREATE TRIGGER aiu_booking_audit ON Booking
AFTER update, delete
AS
DECLARE @event_type varchar(42)
IF EXISTS(SELECT * FROM inserted)
	AND EXISTS(SELECT * FROM deleted)
    SELECT @event_type = 'update'
ELSE
	SELECT @event_type = 'delete'

insert into booking_audit
	  (code,
	   agency,
	   airline_code,
	   flight_number,
	   customer_id,
	   booking_date,
	   flight_date,
	   price,
	   status,
	   udated_by,
	   operation_type)
select code,
	   agency,
	   airline_code,
	   flight_number,
	   customer_id,
	   booking_date,
	   flight_date,
	   price,
	   status,
	   SUSER_SNAME(),
	   @event_type
  from deleted;

-- check trigger
select * from Booking
 where code in ('YV298P', 'YK298P');

update Booking
   set customer_id = 2
 where code = 'YV298P';

delete from Booking where code = 'YK298P';

select *
  from booking_audit;