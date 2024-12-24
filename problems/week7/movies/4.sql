-- Output a table with a single column and a single row containing the number of movies with a 10.0 rating
SELECT COUNT(movie_id) FROM ratings WHERE rating = 10.0; 