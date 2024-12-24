-- Output a table with a single column for the name of each song for the 5 longest songs
SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;