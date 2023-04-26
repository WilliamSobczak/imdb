#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <unordered_set>

using namespace std;

class Movie {
public:
    string tconst;
    string titleType;
    string primaryTitle;
    float averageRating;
    int numVotes;
    int startYear;
    int runtimeMinutes;
    string genre1;
    string genre2;
    string genre3;

    Movie(string tconst, string titleType, string primaryTitle, float averageRating = -1, int numVotes = -1, int startYear = -1, int runtimeMinutes = -1, string genre1 = "NA", string genre2 = "NA", string genre3 = "NA") {
        this->tconst = tconst;
        this->titleType = titleType;
        this->primaryTitle = primaryTitle;
        this->averageRating = averageRating;
        this->numVotes = numVotes;
        this->startYear = startYear;
        this->runtimeMinutes = runtimeMinutes;
        this->genre1 = genre1;
        this->genre2 = genre2;
        this->genre3 = genre3;
    }
    Movie() {
        tconst = "";
        titleType = "";
        primaryTitle = "";
        averageRating = -1;
        numVotes = -1;
        startYear = -1;
        runtimeMinutes = -1;
        genre1 = "NA";
        genre2 = "NA";
        genre3 = "NA";
    }
};


void printMovies(const vector<Movie>& movies, int number_of_rows) {
    std::cout << setw(12) << left << "Movie #"
         << setw(15) << left << "tconst"
         << setw(12) << left << "titleType"
         << setw(70) << left << "primaryTitle"
         << setw(15) << left << "averageRating"
         << setw(10) << left << "numVotes"
         << setw(10) << left << "startYear"
         << setw(15) << left << "runtimeMinutes"
         << setw(15) << left << "genre1"
         << setw(15) << left << "genre2"
         << setw(2) << left << "genre3"
         << endl;
    if (number_of_rows == -1 || number_of_rows >= movies.size()) {
        for (int i = 0; i < movies.size(); i++) {
            std::cout << setw(12) << left << i + 1
            << setw(15) << left << movies[i].tconst
            << setw(12) << left << movies[i].titleType
            << setw(70) << left << movies[i].primaryTitle
            << setw(15) << left << movies[i].averageRating
            << setw(10) << left << movies[i].numVotes
            << setw(10) << left << movies[i].startYear
            << setw(15) << left << movies[i].runtimeMinutes
            << setw(15) << left << movies[i].genre1
            << setw(15) << left << movies[i].genre2
            << setw(2) << left << movies[i].genre3
            << endl;
        }
    }
    else {
        for (int i = 0; i < number_of_rows; i++) {
            std::cout << setw(12) << left << i + 1
             << setw(15) << left << movies[i].tconst
             << setw(12) << left << movies[i].titleType
             << setw(70) << left << movies[i].primaryTitle
             << setw(15) << left << movies[i].averageRating
             << setw(10) << left << movies[i].numVotes
             << setw(10) << left << movies[i].startYear
             << setw(15) << left << movies[i].runtimeMinutes
             << setw(15) << left << movies[i].genre1
             << setw(15) << left << movies[i].genre2
             << setw(2) << left << movies[i].genre3
             << endl;
        }
    }
}

void merge(vector<Movie>& movies, int l, int m, int r, bool ascending) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<Movie> L(n1);
    vector<Movie> R(n2);

    for (i = 0; i < n1; i++)
        L[i] = movies[l + i];
    for (j = 0; j < n2; j++)
        R[j] = movies[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if ((ascending && L[i].averageRating <= R[j].averageRating) || (!ascending && L[i].averageRating >= R[j].averageRating)) {
            movies[k] = L[i];
            i++;
        }
        else {
            movies[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        movies[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        movies[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Movie>& movies, int l, int r, bool ascending) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(movies, l, m, ascending);
        mergeSort(movies, m + 1, r, ascending);
        merge(movies, l, m, r, ascending);
    }
}

int partition(vector<Movie>& movies, int low, int high, bool ascending) {
    float pivot = movies[high].averageRating;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if ((ascending && movies[j].averageRating <= pivot) || (!ascending && movies[j].averageRating >= pivot)) {
            i++;
            swap(movies[i], movies[j]);
        }
    }
    swap(movies[i + 1], movies[high]);
    return i + 1;
}

void quickSort(vector<Movie>& movies, int low, int high, bool ascending) {
    if (low < high) {
        int pivot = partition(movies, low, high, ascending);
        quickSort(movies, low, pivot - 1, ascending);
        quickSort(movies, pivot + 1, high, ascending);
    }
}

int main() {
    vector<Movie> movies;
    long totalRuntime = 0;
    ifstream file("Text.txt");
    string line;
    getline(file, line); // skip first line (header)
    while (getline(file, line)) {
        string tconst, titleType, primaryTitle, averageRatingStr, numVotesStr, startYearStr, runtimeMinutesStr, genre1, genre2, genre3;
        float averageRating;
        int numVotes, startYear, runtimeMinutes;
        stringstream ss(line);
        getline(ss, tconst, '\t');
        getline(ss, titleType, '\t');
        getline(ss, primaryTitle, '\t');
        getline(ss, averageRatingStr, '\t');
        if (averageRatingStr == "NA") averageRating = -1;
        else averageRating = stof(averageRatingStr);
        getline(ss, numVotesStr, '\t');
        if (numVotesStr == "NA") numVotes = -1;
        else numVotes = stoi(numVotesStr);
        getline(ss, startYearStr, '\t');
        if (startYearStr == "NA") startYear = -1;
        else startYear = stoi(startYearStr);
        getline(ss, runtimeMinutesStr, '\t');
        if (runtimeMinutesStr == "NA") runtimeMinutes = -1;
        else runtimeMinutes = stoi(runtimeMinutesStr);
        getline(ss, genre1, '\t');
        getline(ss, genre2, '\t');
        getline(ss, genre3, '\t');
        movies.push_back(Movie(tconst, titleType, primaryTitle, averageRating, numVotes, startYear, runtimeMinutes, genre1, genre2, genre3));
    }
    file.close();


    //User Menu/ Console Interface
    int main_menu_selection = -1;
    vector<Movie> moviesFiltered;
    bool filter_chosen = false;


    int year_lower_bound = -1;
    int year_upper_bound = -1;
    unordered_set<string> genres;
    unordered_set<string> title_types;
    int runtime_lower_bound = -1;
    int runtime_upper_bound = -1;
    int votes_lower_bound = -1;
    int votes_upper_bound = -1;
    float rating_lower_bound = -1;
    float rating_upper_bound = -1;


    while (main_menu_selection != 0) {
        cout << "\n\nSelect Movie Filter:\n1. Year\n2. Genre\n3. Title Type\n4. Runtime\n5. Number of Votes\n6. Rating\n0. No further filters\n" << endl;
        cin >> main_menu_selection;
        if (main_menu_selection != 0) {
            filter_chosen = true;
        }
        if (main_menu_selection == 1) {
            cout << "Enter Year Lower Bound" << endl;
            cin >> year_lower_bound;
            cout << "Enter Year Upper Bound" << endl; 
            cin >> year_upper_bound;
        }
        else if (main_menu_selection == 2) {
            cout << "Enter a comma separated list of genres to include:\nOptions include Comedy, Drama, Romance, Western, Biography, Adventure, Music, Mystery, Family, Animation, Film-Noir, Crime, War, Sci-Fi, Horror, Thriller, Musical\n" << endl;
            string genre_input = "";
            cin >> genre_input;
            std::stringstream ss(genre_input);
            std::string genre;
            while (std::getline(ss, genre, ',')) {
                // Insert each element into the unordered set
                genres.insert(genre);
            }
            genre_input = "";
        }
        else if (main_menu_selection == 3) {
            cout << "Enter a comma separated list of title types to include:\nOptions include Movie, Short, tvSeries\n" << endl;
            string title_type_input = "";
            cin >> title_type_input;
            std::stringstream ss(title_type_input);
            std::string title_type;
            while (std::getline(ss, title_type, ',')) {
                // Insert each element into the unordered set
                title_types.insert(title_type);
            }
            title_type_input = "";
        }
        else if (main_menu_selection == 4) {
            cout << "Enter runtime lower bound in minutes:\n" << endl;
            cin >> runtime_lower_bound;
            cout << "Enter Year Upper Bound" << endl; 
            cin >> runtime_upper_bound;
        }
        else if (main_menu_selection == 5) {
            cout << "Enter number of votes lower bound:\n" << endl;
            cin >> votes_lower_bound;
            cout << "Enter number of votes upper bound:\n" << endl;
            cin >> votes_upper_bound;
        }
        else if (main_menu_selection == 6) {
            cout << "Enter rating (0.0 - 10.0) lower bound:\n" << endl;
            cin >> rating_lower_bound;
            cout << "Enter rating (0.0 - 10.0) upper bound:\n" << endl;
            cin >> rating_upper_bound;
        }
    }
    

    if (filter_chosen) {
        //applying filters to movies
        for (int i = 0; i < movies.size(); i++) {
            //Year constraints
            if (year_upper_bound!=-1 and year_lower_bound != -1) {
                if (movies[i].startYear <= year_upper_bound && movies[i].startYear >= year_lower_bound) {
                    moviesFiltered.push_back(movies[i]);
                }

            }
            else if(year_upper_bound != -1) {
                if (movies[i].startYear <= year_upper_bound) {
                    moviesFiltered.push_back(movies[i]);
                }
            }
            else if (year_lower_bound != -1) {
                if (movies[i].startYear >= year_lower_bound) {
                    moviesFiltered.push_back(movies[i]);
                }
            }

            //genre constraints
            if (!genres.empty()) {
                if (genres.count(movies[i].genre1)==1 || genres.count(movies[i].genre2)==1 || genres.count(movies[i].genre3)==1) {
                    moviesFiltered.push_back(movies[i]);
                }
            }

            //title_types constraints
            if (!title_types.empty()) {
                if (genres.count(movies[i].titleType)==1) {
                    moviesFiltered.push_back(movies[i]);
                }
            }

            //runtime constraints
            if (runtime_upper_bound!=-1 and runtime_lower_bound != -1) {
                if (movies[i].runtimeMinutes <= runtime_upper_bound && movies[i].runtimeMinutes >= runtime_lower_bound) {
                    moviesFiltered.push_back(movies[i]);
                }
            }
            else if(runtime_upper_bound != -1) {
                if (movies[i].runtimeMinutes <= runtime_upper_bound) {
                    moviesFiltered.push_back(movies[i]);
                }
            }
            else if (runtime_lower_bound != -1) {
                if (movies[i].runtimeMinutes >= runtime_lower_bound) {
                    moviesFiltered.push_back(movies[i]);
                }

            }

            //votes constraints
            if (votes_upper_bound!=-1 and votes_lower_bound != -1) {
                if (movies[i].numVotes <= votes_upper_bound && movies[i].numVotes >= votes_lower_bound) {
                    moviesFiltered.push_back(movies[i]);
                }
            }
            else if(votes_upper_bound != -1) {
                if (movies[i].numVotes <= votes_upper_bound) {
                    moviesFiltered.push_back(movies[i]);
                }
            }
            else if (votes_lower_bound != -1) {
                if (movies[i].numVotes >= votes_lower_bound) {
                    moviesFiltered.push_back(movies[i]);
                }
            }

            //rating constraints
            if (rating_upper_bound!=-1 and rating_lower_bound != -1) {
                if (movies[i].averageRating <= rating_upper_bound && movies[i].averageRating >= rating_lower_bound) {
                    moviesFiltered.push_back(movies[i]);
                }
            }
            else if(rating_upper_bound != -1) {
                if (movies[i].averageRating <= rating_upper_bound) {
                    moviesFiltered.push_back(movies[i]);
                }
            }
            else if (rating_lower_bound != -1) {
                if (movies[i].averageRating >= rating_lower_bound) {
                    moviesFiltered.push_back(movies[i]);
                }
            }

        }

    }
    else {
        moviesFiltered = movies;
    }


    // "Ascending/decending/limit selections"
    int ordering_choice = 1;
    int limit_choice = 1;
    int number_of_rows = -1;

    cout << "Show results by (1) ratings ascending or (2) ratings descending?" << endl;
    cin >> ordering_choice;

    cout << "Limit Number Rows of Output?\n1. Show all\n2. Specify number" << endl;
    cin >> limit_choice;
    if (limit_choice == 2) {
        cout << "Enter maximum rows of data displayed" << endl;
        cin >> number_of_rows;
    }
    

    auto merge_start_time = chrono::high_resolution_clock::now();
    auto quick_start_time = chrono::high_resolution_clock::now();

    if (ordering_choice ==1) {
        mergeSort(moviesFiltered, 0, moviesFiltered.size() - 1, true); 
    }
    else {
        mergeSort(moviesFiltered, 0, moviesFiltered.size() - 1, false); 
    }
    
    auto merge_end_time = chrono::high_resolution_clock::now();

    if (ordering_choice ==1) {
        quickSort(moviesFiltered, 0, moviesFiltered.size() - 1, true); 
    }
    else {
        quickSort(moviesFiltered, 0, moviesFiltered.size() - 1, false); 
    }
    auto quick_end_time = chrono::high_resolution_clock::now();

    // calculate duration
    auto merge_duration = chrono::duration_cast<chrono::microseconds>(merge_end_time - merge_start_time);
    auto quick_duration = chrono::duration_cast<chrono::microseconds>(quick_end_time - quick_start_time);

    // print movies
    printMovies(moviesFiltered, number_of_rows);

    cout << endl;
    cout << "Time taken by merge sort: " << merge_duration.count() << " microseconds." << endl;
    cout << "Time taken by quick sort: " << quick_duration.count() << " microseconds." << endl;
    if (merge_duration.count() > quick_duration.count()) {
        cout << "Quick Sort was faster than Merge Sort by " << (abs(quick_duration.count() - merge_duration.count()))/(quick_duration.count())*100 << "%" << endl;
    }
    if (merge_duration.count() < quick_duration.count()) {
        cout << "Merge Sort was faster than Quick Sort by " << (abs(merge_duration.count() - quick_duration.count()))/(merge_duration.count())*100 << "%" << endl;
    }
    cout << endl;

    return 0;
}
