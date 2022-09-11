-- SELECT title FROM movies WHERE id IN
-- (SELECT movie_ID from ratings WHERE movie_id IN
-- (SELECT movie_id FROM stars WHERE person_id IN
-- (SELECT id FROM people WHERE name = "Chadwick Boseman"))
-- ORDER by rating DESC
-- LIMIT 5
-- )
SELECT title FROM
movies JOIN ratings ON ratings.movie_id = movies.id
WHERE id IN
(SELECT movie_id FROM stars WHERE person_id IN
(SELECT id FROM people WHERE name = "Chadwick Boseman"))
ORDER by ratings.rating DESC
LIMIT 5