-- Output a table with a single column for the name of each song which features other artists
SELECT name FROM songs WHERE name LIKE '%feat.%';