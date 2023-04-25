#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>

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


void printMovies(const vector<Movie>& movies) {
    cout << setw(8) << left << "Movie #"
         << setw(12) << left << "tconst"
         << setw(12) << left << "titleType"
         << setw(40) << left << "primaryTitle"
         << setw(15) << left << "averageRating"
         << setw(10) << left << "numVotes"
         << setw(10) << left << "startYear"
         << setw(15) << left << "runtimeMinutes"
         << setw(15) << left << "genre1"
         << setw(15) << left << "genre2"
         << setw(15) << left << "genre3"
         << endl;

    for (unsigned int i = 0; i < movies.size(); i++) {
        cout << setw(8) << left << i + 1
             << setw(12) << left << movies[i].tconst
             << setw(12) << left << movies[i].titleType
             << setw(40) << left << movies[i].primaryTitle
             << setw(15) << left << movies[i].averageRating
             << setw(10) << left << movies[i].numVotes
             << setw(10) << left << movies[i].startYear
             << setw(15) << left << movies[i].runtimeMinutes
             << setw(15) << left << movies[i].genre1
             << setw(15) << left << movies[i].genre2
             << setw(15) << left << movies[i].genre3
             << endl;
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


    // start time
    auto start_time = chrono::high_resolution_clock::now();

    // sort movies by ascending averageRating
    mergeSort(movies, 0, movies.size() - 1, true); 
    auto end_time = chrono::high_resolution_clock::now();

    // calculate duration
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    // print movies
    printMovies(movies);


    cout << "Time taken by merge sort: " << duration.count() << " microseconds." << endl;
    return 0;
}
