-- Output a table with two columns, one for the title of each Harry Potter movie and one for the release year of each movie, in chronological orderd
SELECT title, year FROM movies WHERE title LIKE 'Harry Potter%' ORDER BY year;