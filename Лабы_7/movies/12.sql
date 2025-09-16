-- SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = 'Bradley Cooper' or name = 'Jennifer Lawrence'));

SELECT movies.title, people.name FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id WHERE people.name IN ('Bradley Cooper','Jennifer Lawrence');
