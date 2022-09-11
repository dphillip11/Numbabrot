-- SELECT description FROM crime_scene_reports
    -- WHERE day = 28
    -- and month = 7
    -- and year = 2021

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- SELECT * FROM interviews
--     WHERE day = 28
--     and month = 7
--     and year = 2021

-- Ruth:   Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--         If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

-- Eugene: I don't know the thief's name, but it was someone I recognized.
--         Earlier this morning, before I arrived at Emma's bakery,
--         I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- Raymond:    As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--             In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--             The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- KEY INFO:    10:15 - 10:25, car left bakery
            --  Cash withdrawal Leggett Street, 28/7
             -- Phone call, outgoing, 10:15 - 10:25 less than one minute to accomplice
            --  Early flight out of Fiftyville 29/7

-- SELECT name as suspects FROM people

--     WHERE id IN
--     -- cash withdrawal
--         (SELECT person_id FROM
--             bank_accounts JOIN atm_transactions on atm_transactions.account_number = bank_accounts.account_number
--             WHERE atm_transactions.day = 28
--             and atm_transactions.month = 7
--             and atm_transactions.year = 2021)

--     and phone_number IN
--     --  outgoing phone call, less than a minute
--         (SELECT caller FROM phone_calls
--             WHERE day = 28
--             and month = 7
--             and year = 2021
--             and duration < 60)

--     and license_plate IN
--     -- left bakery withing 10 minutes of theft
--         (SELECT license_plate FROM bakery_security_logs
--             WHERE day = 28
--             and month = 7
--             and year = 2021
--             and hour BETWEEN 10 and 11
--             and minute BETWEEN 15 and 25
--             and activity = 'exit')

--     and passport_number IN
--     -- early flight out of Fiftyville on 29/7/2021
--         (SELECT passport_number FROM
--             flights JOIN passengers ON flights.id = passengers.flight_id
--                 WHERE origin_airport_id IN
--                  (SELECT id FROM airports WHERE city LIKE "%fiftyville%")
--                 and flights.day = 29
--                 and flights.month = 7
--                 and flights.year = 2021
--                 ORDER by hour
--                 LIMIT 8)
--                 --  LIMIT 1 didn't produce any results , let's inspect the flight data...

-- SELECT * FROM
--             flights JOIN passengers ON flights.id = passengers.flight_id
--                 WHERE origin_airport_id IN
--                  (SELECT id FROM airports WHERE city LIKE "%fiftyville%")
--                 and flights.day = 29
--                 and flights.month = 7
--                 and flights.year = 2021
--                 ORDER by hour
--                 LIMIT 10

-- +----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 7214083635      | 2A   |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 1695452385      | 3B   |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 5773159633      | 4A   |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 1540955065      | 5C   |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 8294398571      | 6C   |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 1988161715      | 6D   |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 9878712108      | 7A   |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 8496433585      | 7B   |
-- | 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     | 43        | 7597790505      | 7B   |
-- | 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     | 43        | 6128131458      | 8A   |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+

-- Now we can see 8 passengers got on the early flight, so we will set the LIMIT to 8 and repeat the query
-- +----------+
-- | suspects |
-- +----------+
-- | Bruce    | NICE! We have our thief! Where did he go and who was his accomplice?
-- +----------+

-- SELECT city FROM airports
--     WHERE id IN(
--         SELECT destination_airport_id FROM flights
--             WHERE id IN
--                 (SELECT flight_id FROM passengers
--                     WHERE passport_number IN
--                         (SELECT passport_number FROM people WHERE name = 'Bruce')))

-- luckily just one Bruce, flight 36, destination airport 4, New York City

SELECT name FROM people
    WHERE phone_number IN(
        SELECT receiver FROM phone_calls
            WHERE caller IN (SELECT phone_number FROM people WHERE name = 'Bruce')
            and day = 28
            and month = 7
            and year = 2021
            and duration < 60)

--Just one call fitting the restrictions, made to Robin, this must be our accomplice
