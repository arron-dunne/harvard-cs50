-- Output a table with a single column for the name of each song by Post Malone
SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Post Malone');