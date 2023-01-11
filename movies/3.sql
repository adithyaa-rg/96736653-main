CREATE INDEX "year_release" ON movies("year");
CREATE INDEX "title_index" ON movies("title");
SELECT title FROM movies WHERE year>=2018 ORDER BY title;