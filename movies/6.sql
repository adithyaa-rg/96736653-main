SELECT avg(rating) FROM ratings,movies WHERE ratings.movie_id=movies.id AND year=2012;
SELECT avg(rating) FROM ratings WHERE movie_id IN (SELECT id FROM movies WHERE year=2012);