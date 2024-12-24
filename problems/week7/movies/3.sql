-- Output a table with a single column for the title of each movie released in or after 2018, in alphabetical order
SELECT title FROM movies WHERE year >= 2018 ORDER BY title;