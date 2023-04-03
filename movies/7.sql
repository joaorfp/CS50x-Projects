SELECT movies.title, r.rating FROM movies JOIN ratings AS r
ON movies.id = r.movie_id WHERE movies.year = 2010
ORDER BY r.rating DESC, title ASC;

