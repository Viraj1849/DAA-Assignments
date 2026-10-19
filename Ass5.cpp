#include <iostream>
#include <climits>
using namespace std;

const int INF = 999999;

int main() {
    int n, stages;

    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of stages: ";
    cin >> stages;

    int graph[100][100] = {0};
    int edges;

    cout << "Enter number of routes: ";
    cin >> edges;
    cout << "\nEnter route information:\n";
    cout << "Format: source destination cost\n\n";

    for (int i = 0; i < edges; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        graph[u][v] = cost;
    }

    int dp[100];
    int nextVertex[100];
    int path[100];

    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
        nextVertex[i] = -1;
    }

    // Destination
    dp[n] = 0;

    // Dynamic Programming: process vertices in reverse order
    for (int i = n - 1; i >= 1; i--) {
        for (int j = i + 1; j <= n; j++) {
            if (graph[i][j] != 0 && dp[j] != INF) {
                int newCost = graph[i][j] + dp[j];
                if (newCost < dp[i]) {
                    dp[i] = newCost;
                    nextVertex[i] = j;
                }
            }
        }
    }

    // Construct path
    int current = 1;
    int pathLength = 0;

    while (current != -1) {
        path[pathLength++] = current;
        if (current == n) break;
        current = nextVertex[current];
    }

    cout << "\n==============================\n";
    cout << "       SWIFTCARGO RESULT\n";
    cout << "==============================\n";
    if (dp[1] == INF) {
        cout << "No route found.\n";
        return 0;
    }

    cout << "Minimum Cost: " << dp[1] << endl;
    cout << "Optimal Route: ";
    for (int i = 0; i < pathLength; i++) {
        cout << path[i];
        if (i != pathLength - 1) cout << " -> ";
    }
    cout << endl;
    return 0;
}