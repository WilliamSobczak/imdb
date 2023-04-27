#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <unordered_set>

using namespace std;

struct Movie {
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