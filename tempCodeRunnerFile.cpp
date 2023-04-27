 int length_of_movies = movies.size();

    //applying filters to movies
    for (int i = length_of_movies-1; i >= 0; i--) {
        //Year constraints
        if (year_upper_bound!=-1 && year_lower_bound != -1) {
            cout << "year filter applicatoin reached" << endl;
            if (movies[i].startYear > year_upper_bound || movies[i].startYear < year_lower_bound) {
                movies.erase(movies.begin() + i);
                i--;
                continue;
                cout << "decrement reached" << endl;
            }
        }
        else if(year_upper_bound != -1) {
            if (movies[i].startYear > year_upper_bound) {
                movies.erase(movies.begin() + i);
                i--;
                continue;
                
            }
        }
        else if (year_lower_bound != -1) {
            if (movies[i].startYear < year_lower_bound) {
                movies.erase(movies.begin() + i);
                i--;
                continue;
                
            }
        }

        //genre constraints
        if (!genres.empty()) {
            if (genres.count(movies[i].genre1)==0 && genres.count(movies[i].genre2)==0 && genres.count(movies[i].genre3)==0) {
                movies.erase(movies.begin() + i);
                i--;
                continue;
            }
        }

        //title_types constraints
        if (!title_types.empty()) {
            if (title_types.count(movies[i].titleType)==0) {
                movies.erase(movies.begin() + i);
                i--;
                continue;
            }
        }

        //runtime constraints
        if (runtime_upper_bound!=-1 and runtime_lower_bound != -1) {
            if (movies[i].runtimeMinutes > runtime_upper_bound || movies[i].runtimeMinutes < runtime_lower_bound) {
                movies.erase(movies.begin() + i);
                i--;
                continue;
            }
        }
        else if(runtime_upper_bound != -1) {
            if (movies[i].runtimeMinutes > runtime_upper_bound) {
                movies.erase(movies.begin() + i);
                i--;
                continue;
            }
        }
        else if (runtime_lower_bound != -1) {
            if (movies[i].runtimeMinutes < runtime_lower_bound) {
                movies.erase(movies.begin() + i);
                i--;
                continue;
            }

        }

        //votes constraints
        if (votes_upper_bound!=-1 && votes_lower_bound != -1) {
            if (movies[i].numVotes > votes_upper_bound || movies[i].numVotes < votes_lower_bound) {
                movies.erase(movies.begin() + i);
                i--;
                continue;
            }
        }
        else if(votes_upper_bound != -1) {
            if (movies[i].numVotes > votes_upper_bound) {
                movies.erase(movies.begin() + i);
                i--;
                continue;
            }
        }
        else if (votes_lower_bound != -1) {
            if (movies[i].numVotes < votes_lower_bound) {
                movies.erase(movies.begin() + i);
                i--;
                continue;
            }
        }

        //rating constraints
        if (rating_upper_bound!=-1 && rating_lower_bound != -1) {
            if (movies[i].averageRating > rating_upper_bound || movies[i].averageRating < rating_lower_bound) {
                movies.erase(movies.begin() + i);
                i--;
                continue;
            }
        }
        else if(rating_upper_bound != -1) {
            if (movies[i].averageRating > rating_upper_bound) {
                movies.erase(movies.begin() + i);
                i--;
                continue;
            }
        }
        else if (rating_lower_bound != -1) {
            if (movies[i].averageRating < rating_lower_bound) {
                movies.erase(movies.begin() + i);
                i--;
                continue;
            }
        }

    }