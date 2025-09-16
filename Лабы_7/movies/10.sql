-- SELECT DISTINCT name FROM people WHERE id IN (SELECT person_id FROM directors WHERE movie_id IN (SELECT id FROM movies WHERE id IN (SELECT movie_id FROM ratings WHERE rating >= 9.0)));

-- SELECT directors.person_id FROM movies JOIN ratings ON movies.id = ratings.movie_id JOIN directors ON movies.id = directors.movie_id WHERE rating >= 9.0;

SELECT DISTINCT id FROM people WHERE id IN (SELECT directors.person_id FROM movies JOIN ratings ON movies.id = ratings.movie_id JOIN directors ON movies.id = directors.movie_id WHERE rating >= 9.0);
