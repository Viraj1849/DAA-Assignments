
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

struct Movie {
    int movieID;
    string title;
    double imdbRating;
    int releaseYear;
    int popularity;
};

int partition(vector<Movie>& movies, int low, int high) {
    double pivot = movies[high].imdbRating;
    int i = low - 1;

    for(int j=low; j<high; j++) {
        if(movies[j].imdbRating <= pivot) {
            i++;
            swap(movies[i], movies[j]);
        }
    }
    swap(movies[i+1], movies[high]);
    return i+1;
}

void quickSort(vector<Movie>& movies, int low, int high) {
    if(low < high) {
        int pi = partition(movies, low, high);
        quickSort(movies, low, pi-1);
        quickSort(movies, pi+1, high);
    }
}

int main() {
    ifstream file("movies.csv");

    if(!file.is_open()) {
        cout << "Error: Cannot open movies.csv\n";
        return 1;
    }

    vector<Movie> movies;
    string line;
    getline(file, line); // Skip header

    while(getline(file, line)) {
        stringstream ss(line);
        string temp;
        Movie m;

        try {
            getline(ss, temp, ',');
            m.movieID = stoi(temp);

            getline(ss, m.title, ',');

            getline(ss, temp, ',');
            m.imdbRating = stod(temp);

            getline(ss, temp, ',');
            m.releaseYear = stoi(temp);

            getline(ss, temp, ',');
            m.popularity = stoi(temp);

            movies.push_back(m);
        } catch(...) {
            continue;
        }
    }
    file.close();

    if(movies.empty()) {
        cout << "No movies found!\n";
        return 1;
    }

    cout << "Movie Recommendation System\n";
    cout << "Total Movies Loaded: "
         << movies.size() << "\n";

    auto start = high_resolution_clock::now();
    quickSort(movies, 0, (int)movies.size()-1);
    auto stop = high_resolution_clock::now();

    auto duration =
        duration_cast<microseconds>(stop-start);

    cout << "\nMovies Sorted by IMDb Rating (Ascending)\n";
    cout << "ID\tTitle\t\tRating\tYear\tPopularity\n";

    for(const auto& m : movies) {
        cout << m.movieID << "\t"
             << m.title << "\t"
             << m.imdbRating << "\t"
             << m.releaseYear << "\t"
             << m.popularity << "\n";
    }

    cout << "\nQuick Sort Execution Time: "
         << duration.count() << " microseconds\n";

    return 0;
}
