-- Solve the murder mystery using SQL statements on the data in the database (fiftyville.db)
-- Log all SQL statements used in this file


-- Look at the crime scene report
SELECT * FROM crime_scene_reports;


-- Look at crime scene reports that occured on Humphrey Street
SELECT * FROM crime_scene_reports WHERE street = 'Humphrey Street';
-- 7 results


-- Look at crime scene reports that occured on Humphrey Street and on July 28, 2021
SELECT * FROM crime_scene_reports
    WHERE street = 'Humphrey Street'
    AND year = 2021
    AND month = 7
    AND day = 28;
-- 2 results, 1 of which is the duck


-- Narrow down to single crime scene of duck
SELECT * FROM crime_scene_reports
    WHERE street = 'Humphrey Street'
    AND year = 2021
    AND month = 7
    AND day = 28
    AND description LIKE '%duck%';
-- Description: Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time –
-- each of their interview transcripts mentions the bakery.


-- Look for Interviews which contain bakery
SELECT * FROM interviews WHERE transcript LIKE '%bakery%';
-- 4 results (1 result before event)
-- Ruth: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene: I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- Raymond: As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.


-- Follow Ruths lead
SELECT * FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10;
--14 results


-- Narrow it down
SELECT * FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15 AND minute <= 25
    AND activity = 'exit';
-- 8 results:
-- 10:16 - 5P2BI95
-- 10:18 - 94KL13X
-- 10:18 - 6P58WS2
-- 10:19 - 4328GD8
-- 10:20 - G412CB7
-- 10:21 - L93JTIZ
-- 10:23 - 322W7JE
-- 10:23 - 0NTHK55


-- Follow Eugene's lead
SELECT * FROM atm_transactions
    WHERE year = 2021
    AND month = 7
    AND day = 28;
-- Lots of results


-- Narrow it down
SELECT * FROM atm_transactions
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw';
-- 8 results
-- 28500762 £48
-- 28296815 £20
-- 76054385 £60
-- 49610011 £50
-- 16153065 £80
-- 25506511 £20
-- 81061156 £30
-- 26013199 £35


-- Follow Raymond's lead
SELECT * FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28;


-- Narrow it down
SELECT * FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60;
-- 9 results
-- caller (130) 555-0289, receiver: (996) 555-8899
-- caller (499) 555-9472, receiver: (892) 555-8872
-- caller (367) 555-5533, receiver: (375) 555-8161
-- caller (499) 555-9472, receiver: (717) 555-1342
-- caller (286) 555-6063, receiver: (676) 555-6554
-- caller (770) 555-1861, receiver: (725) 555-3243
-- caller (031) 555-6622, receiver: (910) 555-3251
-- caller (826) 555-1652, receiver: (066) 555-9701
-- caller (338) 555-6650, receiver: (704) 555-2131


-- Look for the first flight of the next day
SELECT * FROM flights
    WHERE year = 2021
    AND month = 7
    AND day = 29
    AND origin_airport_id = (
        SELECT id FROM airports WHERE city = 'Fiftyville'
    )
    ORDER BY hour, minute;
-- 5 results, the top 1
-- Flight ID: 36, Dest_id 4 @ 8:20


-- Get people on that flight
SELECT * FROM passengers WHERE flight_id = 36;
-- 7214083635 | 2A
-- 1695452385 | 3B
-- 5773159633 | 4A
-- 1540955065 | 5C
-- 8294398571 | 6C
-- 1988161715 | 6D
-- 9878712108 | 7A
-- 8496433585 | 7B


-- Find the culprit!
SELECT id, name FROM people
    WHERE phone_number IN (
        SELECT caller FROM phone_calls
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND duration < 60
    )
    AND passport_number IN (
        SELECT passport_number FROM passengers
            WHERE flight_id = (
                SELECT id FROM flights
                    WHERE year = 2021
                    AND month = 7
                    AND day = 29
                    AND origin_airport_id = (
                        SELECT id FROM airports WHERE city = 'Fiftyville'
                    )
                    ORDER BY hour, minute
                    LIMIT(1)
            )
    )
    AND license_plate IN (
        SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= 15 AND minute <= 25
    )
    AND id IN (
        SELECT person_id FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number FROM atm_transactions
                    WHERE year = 2021
                    AND month = 7
                    AND day = 28
                    AND atm_location = 'Leggett Street'
                    AND transaction_type = 'withdraw'
            )
    );
-- 686048 | Bruce


-- Find destination
SELECT city FROM airports
    WHERE id = (
        SELECT destination_airport_id FROM flights
            WHERE year = 2021
            AND month = 7
            AND day = 29
            AND origin_airport_id = (
                SELECT id FROM airports WHERE city = 'Fiftyville'
            )
            ORDER BY hour, minute
            LIMIT(1)
    );
-- New York City


-- Find the Accomplice
SELECT id, name FROM people
    WHERE phone_number = (
        SELECT receiver FROM phone_calls
            WHERE caller = (
                SELECT phone_number FROM people
                    WHERE id = 686048
            )
            AND year = 2021
            AND month = 7
            AND day = 28
            AND duration < 60
    );
-- 864400 Robin