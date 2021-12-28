-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Check reports from 28th of july
select description from crime_scene_reports where day = 28 and month = 7 and year = 2020;
-- All of the reports of the crime mention the courthouse

-- Look for interviews from 28th of july that mention the courthouse
select transcript from interviews where year = 2020 and month = 7 and day = 28 and transcript like '%courthouse%';
-- The thief left the parking lot within 10 minutes of the crime; check security logs in that time frame
-- The thief has withdrawn money from the ATM on Fifer Street that morning; check ATM transactions on that day
-- While leaving the thief called someone, the call lasted less than a minute, the thief was supposed to take the first flight out of Fiftyville the next day, the other person was to purchase the plane ticket; check phonecalls that morning and flights the next day

-- Look for cars exiting the parking lot within the time frame
select license_plate from courthouse_security_logs where year = 2020 and month = 7 and day = 28 and hour = 10 and minute >= 15 and minute <= 25 and activity = 'exit';
-- The license plates can be used to narrow down the search for the thief; track the plates to people:
-- 5P2BI95
-- 94KL13X
-- 6P58WS2
-- 4328GD8
-- G412CB7
-- L93JTIZ
-- 322W7JE
-- 0NTHK55

-- Look for account numbers which have withdrawn money from the ATM on Fifer Street on the day of the crime;
select account_number from atm_transactions where atm_location = 'Fifer Street' and year = 2020 and month = 7 and day = 28 and transaction_type = 'withdraw';
-- Account numbers can be used to narrow the search for the thief; track the account numbers to people:
-- 28500762
-- 28296815
-- 76054385
-- 49610011
-- 16153065
-- 25506511
-- 81061156
-- 26013199

-- Look for numbers from phone calls from 28th of july which lasted less than a minute
select caller, receiver from phone_calls where year = 2020 and month = 7 and day = 28 and duration < 60;
-- Phone numbers can be used to identify the thief and the accomplice (the caller is the thief, the receiver is the accomplice); track the numbers to people
-- (130) 555-0289|(996) 555-8899
-- (499) 555-9472|(892) 555-8872
-- (367) 555-5533|(375) 555-8161
-- (499) 555-9472|(717) 555-1342
-- (286) 555-6063|(676) 555-6554
-- (770) 555-1861|(725) 555-3243
-- (031) 555-6622|(910) 555-3251
-- (826) 555-1652|(066) 555-9701
-- (338) 555-6650|(704) 555-2131

-- Look for people with the license plates
select name from people where license_plate in (select license_plate from courthouse_security_logs where year = 2020 and month = 7 and day = 28 and hour = 10 and minute >= 15 and minute <= 25 and activity = 'exit');
-- The culprit must be among these people; find out which people match with the account numbers obtained before
-- Patrick
-- Amber
-- Elizabeth
-- Roger
-- Danielle
-- Russell
-- Evelyn
-- Ernest

-- Look for people with license plates matching the account numbers
select name from people join bank_accounts on bank_accounts.person_id = people.id where name in (select name from people where license_plate in (select license_plate from courthouse_security_logs where year = 2020 and month = 7 and day = 28 and hour = 10 and minute >= 15 and minute <= 25 and activity = 'exit')) and account_number in (select account_number from atm_transactions where atm_location = 'Fifer Street' and year = 2020 and month = 7 and day = 28 and transaction_type = 'withdraw');
-- 
--Ernest
--Russell
--Elizabeth
--Danielle

-- Look for people with matching license plates, phone numbers and account numbers
select name from people where phone_number in (select caller from phone_calls where year = 2020 and month = 7 and day = 28 and duration < 60) and name in (select name from people join bank_accounts on bank_accounts.person_id = people.id where name in (select name from people where license_plate in (select license_plate from courthouse_security_logs where year = 2020 and month = 7 and day = 28 and hour = 10 and minute >= 15 and minute <= 25 and activity = 'exit')) and account_number in (select account_number from atm_transactions where atm_location = 'Fifer Street' and year = 2020 and month = 7 and day = 28 and transaction_type = 'withdraw'));
-- There are still 2 suspects, check which one of them left town in the first flight the next day
-- Russell
-- Ernest

-- Find the id of the Fiftyville airport
select id from airports where full_name = 'Fiftyville Regional Airport';
-- The id is 8

-- Find the id of the first flight the day after the crime
select id from flights where year = 2020 and month = 7 and day = 29 order by hour asc, minute asc limit 1;
-- The id is 36

-- Find which of the last 2 suspects was on the earliest flight the day after the crime
select name from people join passengers on passengers.passport_number = people.passport_number join flights on flights.id = passengers.flight_id where name in (select name from people where phone_number in (select caller from phone_calls where year = 2020 and month = 7 and day = 28 and duration < 60) and name in (select name from people join bank_accounts on bank_accounts.person_id = people.id where name in (select name from people where license_plate in (select license_plate from courthouse_security_logs where year = 2020 and month = 7 and day = 28 and hour = 10 and minute >= 15 and minute <= 25 and activity = 'exit')) and account_number in (select account_number from atm_transactions where atm_location = 'Fifer Street' and year = 2020 and month = 7 and day = 28 and transaction_type = 'withdraw'))) and flight_id  = 36;
-- Ernest is the culprit

-- Find the accomplice's name based on Ernest's phone number
select name from people where phone_number = (select receiver from phone_calls where year = 2020 and month = 7 and day = 28 and caller = (select phone_number from people where name = 'Ernest'));
-- Berthold is the accomplice

-- Find the city Ernest esceped to
select city from airports where id = (select destination_airport_id from flights where id = 36);
-- Ernest escaped to London