SELECT title FROM movies,ratings WHERE id IN
(SELECT movie_id FROM stars WHERE person_id =
(SELECT id FROM people WHERE name="Chadwick Boseman"))
AND movie_id=id
ORDER BY rating desc;