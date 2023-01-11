SELECT DISTINCT title FROM stars,movies WHERE
movie_id in
(
SELECT movie_id FROM stars WHERE person_id=
(SELECT id FROM people WHERE name = 'Johnny Depp')
intersect
SELECT movie_id FROM stars WHERE person_id=
(SELECT id FROM people WHERE name = 'Helena Bonham Carter')
)
AND movie_id=id;