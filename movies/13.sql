SELECT name FROM people where id in
(SELECT DISTINCT person_id FROM stars WHERE movie_id in
(SELECT movie_id FROM stars,people WHERE id=person_id AND name="Kevin Bacon" AND year=1958));