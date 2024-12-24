-- Output a table with a single column and a single row containing the average energy for songs by Drake
SELECT AVG(energy) FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Drake');