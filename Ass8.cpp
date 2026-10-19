#include <iostream>
#include <iomanip>
using namespace std;

#define MAX 20
#define INF 999999

int n;
int cost[MAX][MAX];
int timeTaken[MAX][MAX];
int bestCost = INF;
int bestTime = INF;
int bestPath[MAX + 1];
int path[MAX + 1];
bool visited[MAX];

int findMinCost(int city) {
    int minCost = INF;
    for (int i = 0; i < n; i++) {
        if (i != city && cost[city][i] < minCost)
            minCost = cost[city][i];
    }
    return minCost;
}

int calculateInitialBound() {
    int bound = 0;
    for (int i = 0; i < n; i++)
        bound += findMinCost(i);
    return bound;
}

void TSP(int currentCity, int currentCost, int currentTime, int level) {
    if (level == n) {
        if (cost[currentCity][0] != INF) {
            int totalCost = currentCost + cost[currentCity][0];
            int totalTime = currentTime + timeTaken[currentCity][0];

            if (totalCost < bestCost) {
                bestCost = totalCost;
                bestTime = totalTime;
                for (int i = 0; i < n; i++)
                    bestPath[i] = path[i];
                bestPath[n] = 0;
            }
        }
        return;
    }

    for (int nextCity = 0; nextCity < n; nextCity++) {
        if (!visited[nextCity] && cost[currentCity][nextCity] != INF) {
            int newCost = currentCost + cost[currentCity][nextCity];
            int newTime = currentTime + timeTaken[currentCity][nextCity];

            int lowerBound = newCost;
            for (int i = 0; i < n; i++) {
                if (!visited[i])
                    lowerBound += findMinCost(i);
            }

            if (lowerBound < bestCost) {
                visited[nextCity] = true;
                path[level] = nextCity;
                TSP(nextCity, newCost, newTime, level + 1);
                visited[nextCity] = false;
            }
        }
    }
}

void solveTSP() {
    bestCost = INF;
    bestTime = INF;
    for (int i = 0; i < n; i++)
        visited[i] = false;

    path[0] = 0;
    visited[0] = true;
    TSP(0, 0, 0, 1);

    if (bestCost == INF) {
        cout << "\nNo possible route exists.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << " OPTIMAL DELIVERY ROUTE\n";
    cout << "========================================\n";
    cout << "Route: ";
    for (int i = 0; i <= n; i++) {
        cout << "City " << bestPath[i] + 1;
        if (i < n) cout << " -> ";
    }
    cout << "\n";
    cout << "Minimum Fuel/Travel Cost : " << bestCost << endl;
    cout << "Total Delivery Time : " << bestTime << endl;
    cout << "========================================\n";
}

void displayCostMatrix() {
    cout << "\nCost Matrix:\n\n";
    cout << setw(8) << " ";
    for (int i = 0; i < n; i++)
        cout << setw(8) << "C" << i + 1;
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(8) << "C" << i + 1;
        for (int j = 0; j < n; j++) {
            if (cost[i][j] == INF)
                cout << setw(8) << "-";
            else
                cout << setw(8) << cost[i][j];
        }
        cout << endl;
    }
}

void displayTimeMatrix() {
    cout << "\nTime Matrix:\n\n";
    cout << setw(8) << " ";
    for (int i = 0; i < n; i++)
        cout << setw(8) << "C" << i + 1;
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(8) << "C" << i + 1;
        for (int j = 0; j < n; j++) {
            if (timeTaken[i][j] == INF)
                cout << setw(8) << "-";
            else
                cout << setw(8) << timeTaken[i][j];
        }
        cout << endl;
    }
}

void inputData() {
    cout << "\nEnter number of cities: ";
    cin >> n;
    if (n < 2 || n > MAX) {
        cout << "Invalid number of cities!\n";
        n = 0;
        return;
    }

    cout << "\nEnter cost matrix:\n";
    cout << "(Enter 0 for same city)\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
            if (i == j) cost[i][j] = INF;
        }
    }

    cout << "\nEnter time matrix:\n";
    cout << "(Enter 0 for same city)\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> timeTaken[i][j];
            if (i == j) timeTaken[i][j] = INF;
        }
    }

    cout << "\nData entered successfully!\n";
}

void updateCost() {
    int from, to, newCost;
    cout << "\nEnter source city: ";
    cin >> from;
    cout << "Enter destination city: ";
    cin >> to;
    cout << "Enter new cost: ";
    cin >> newCost;

    if (from >= 1 && from <= n && to >= 1 && to <= n) {
        cost[from - 1][to - 1] = newCost;
        cout << "Cost updated successfully!\n";
    } else {
        cout << "Invalid city number!\n";
    }
}

void updateTime() {
    int from, to, newTime;
    cout << "\nEnter source city: ";
    cin >> from;
    cout << "Enter destination city: ";
    cin >> to;
    cout << "Enter new time: ";
    cin >> newTime;

    if (from >= 1 && from <= n && to >= 1 && to <= n) {
        timeTaken[from - 1][to - 1] = newTime;
        cout << "Time updated successfully!\n";
    } else {
        cout << "Invalid city number!\n";
    }
}

int main() {
    int choice;
    cout << "============================================\n";
    cout << " SWIFTSHIP DELIVERY ROUTE OPTIMIZER\n";
    cout << " LC BRANCH AND BOUND ALGORITHM\n";
    cout << "============================================\n";

    do {
        cout << "\n\n--------------- MENU ----------------\n";
        cout << "1. Enter City Data\n";
        cout << "2. Display Cost Matrix\n";
        cout << "3. Display Time Matrix\n";
        cout << "4. Find Optimal Route\n";
        cout << "5. Update Travel Cost\n";
        cout << "6. Update Travel Time\n";
        cout << "7. Exit\n";
        cout << "-------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            inputData();
            break;
        case 2:
            if (n > 0) displayCostMatrix();
            else cout << "\nPlease enter city data first.\n";
            break;
        case 3:
            if (n > 0) displayTimeMatrix();
            else cout << "\nPlease enter city data first.\n";
            break;
        case 4:
            if (n > 0) solveTSP();
            else cout << "\nPlease enter city data first.\n";
            break;
        case 5:
            if (n > 0) updateCost();
            else cout << "\nPlease enter city data first.\n";
            break;
        case 6:
            if (n > 0) updateTime();
            else cout << "\nPlease enter city data first.\n";
            break;
        case 7:
            cout << "\nThank you for using SwiftShip Route Optimizer!\n";
            break;
        default:
            cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}