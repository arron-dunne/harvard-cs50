-- Output a table with a single column for the title of each the top 5 highest rated movies Chadwick Boseman starred in
SELECT title FROM movies
INNER JOIN ratings ON id = ratings.movie_id
WHERE id IN (
    SELECT movie_id FROM stars WHERE person_id = (
        SELECT id FROM people WHERE name = 'Chadwick Boseman'
    )
)
ORDER BY ratings.rating DESC
LIMIT(5)
;