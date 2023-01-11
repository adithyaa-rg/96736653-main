CREATE INDEX "movie-id","person-id" ON directors("movie_id","person_id");
CREATE INDEX "id_person" ON people("id");
CREATE INDEX "movie-id","person-id" ON ratings("movie_id","person_id");
SELECT DISTINCT name FROM people,directors,movies,ratings WHERE people.id=directors.person_id AND directors.movie_id=ratings.movie_id AND directors.movie_id=movies.id AND rating>9;