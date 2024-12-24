-- Output a table with a single column for the title of each movie that both Johnny Depp and Helena Bonham Carter starred in
SELECT title FROM movies WHERE
id IN (
    SELECT movie_id FROM stars WHERE person_id = (
        SELECT id FROM people WHERE name = 'Johnny Depp'
    )
)
AND id IN (
    SELECT movie_id FROM stars WHERE person_id = (
        SELECT id FROM people WHERE name = 'Helena Bonham Carter'
    )
);
