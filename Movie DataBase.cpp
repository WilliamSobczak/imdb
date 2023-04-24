#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
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

int main() {
    vector<Movie> movies;
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

    mergeSort(movies, 0, movies.size() - 1, true); 
    // sort movies by ascending averageRating
    // print movies
    for (unsigned int i = 0; i < movies.size(); i++) {
        cout << "Movie " << i + 1 << ":" << endl;
        cout << "tconst: " << movies[i].tconst << endl;
        cout << "titleType: " << movies[i].titleType << endl;
        cout << "primaryTitle: " << movies[i].primaryTitle << endl;
        cout << "averageRating: " << movies[i].averageRating << endl;
        cout << "numVotes: " << movies[i].numVotes << endl;
        cout << "startYear: " << movies[i].startYear << endl;
        cout << "runtimeMinutes: " << movies[i].runtimeMinutes << endl;
        cout << "genre1: " << movies[i].genre1 << endl;
        cout << "genre2: " << movies[i].genre2 << endl;
        cout << "genre3: " << movies[i].genre3 << endl;
        cout << endl;
    }
    return 0;
}
