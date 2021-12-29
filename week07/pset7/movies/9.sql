select distinct name from stars join movies on stars.movie_id = movies.id join people on people.id = stars.person_id where year = 2004 order by birth;