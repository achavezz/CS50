-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Looking at the crime report
SELECT description, year FROM crime_scene_reports
WHERE month = 7 and day = 28
AND street = "Humphrey Street";

-- Reading the interviews of the crime
SELECT name, transcript FROM interviews
WHERE month = 7 and day = 28;

-- Looking at the bakery security log
SELECT license_plate, activity, hour, minute FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10;

-- Refining previous query to see cars coming in close to 10
SELECT license_plate, activity, hour, minute FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 9;

-- Looking at phone calls during the time of robbery
SELECT p1.name, p2.name, duration FROM phone_calls
JOIN people AS p1 ON p1.phone_number = phone_calls.caller
JOIN people AS p2 ON p2.phone_number = phone_calls.receiver
WHERE month = 7 AND day = 28 AND year = 2021 AND duration < 70;

-- Looking at the ATM transactions during the time of robbery to find info on accomplice
SELECT account_number, amount FROM atm_transactions
WHERE month = 7 AND year = 2021 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

-- Using previous query, look up the owners of the account numbers of the list

SELECT people.name, bank_accounts.account_number FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE bank_accounts.account_number IN(SELECT account_number FROM atm_transactions
WHERE month = 7 AND year = 2021 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw");

-- Looking at the people who were on a flight the next morning
SELECT people.name, a1.city, a2.city, flights.hour, flights.minute FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports AS a1 ON a1.id = flights.origin_airport_id
JOIN airports AS a2 ON a2.id = flights.destination_airport_id
WHERE flights.month = 7 AND flights.day = 29 AND a1.city = "Fiftyville"
ORDER BY flights.hour, flights.minute;

-- Getting the carowners names from the security logs
SELECT people.name, people.license_plate, activity, hour, minute FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE month = 7 AND day = 28 AND year = 2021 AND (hour = 9 OR hour = 10)
ORDER BY hour, minute;