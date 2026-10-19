#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits>
#include <algorithm>
using namespace std;

using Edge = pair<string, int>; // destination, travel time

map<string, vector<Edge>> graph = {
    {"S", {{"A", 4}, {"B", 2}}},
    {"A", {{"S", 4}, {"B", 1}, {"C", 5}}},
    {"B", {{"S", 2}, {"A", 1}, {"C", 3}, {"D", 10}}},
    {"C", {{"A", 5}, {"B", 3}, {"D", 8}}},
    {"D", {{"B", 10}, {"C", 8}}}
};

vector<string> hospitals = {"C", "D"};

void updateRoad(string start, string end, int newTime) {
    for (auto &edge : graph[start])
        if (edge.first == end) edge.second = newTime;

    for (auto &edge : graph[end])
        if (edge.first == start) edge.second = newTime;
}

void findNearestHospital(string source) {
    const int INF = numeric_limits<int>::max();
    map<string, int> distance;
    map<string, string> previous;

    for (const auto &node : graph)
        distance[node.first] = INF;

    distance[source] = 0;
    priority_queue<pair<int, string>,
                   vector<pair<int, string>>,
                   greater<pair<int, string>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        string currentNode = pq.top().second;
        pq.pop();

        if (currentDistance > distance[currentNode]) continue;

        for (const auto &edge : graph[currentNode]) {
            string neighbour = edge.first;
            int weight = edge.second;

            if (distance[currentNode] != INF &&
                distance[currentNode] + weight < distance[neighbour]) {
                distance[neighbour] = distance[currentNode] + weight;
                previous[neighbour] = currentNode;
                pq.push({distance[neighbour], neighbour});
            }
        }
    }

    string nearestHospital = hospitals[0];
    for (const string &hospital : hospitals)
        if (distance[hospital] < distance[nearestHospital])
            nearestHospital = hospital;

    if (distance[nearestHospital] == INF) {
        cout << "No reachable hospital.\n";
        return;
    }

    vector<string> path;
    for (string current = nearestHospital; ; current = previous[current]) {
        path.push_back(current);
        if (current == source) break;
        if (!previous.count(current)) {
            cout << "Path unavailable.\n";
            return;
        }
    }
    reverse(path.begin(), path.end());

    cout << "\n--- Emergency Route ---\n";
    cout << "Nearest hospital: " << nearestHospital << endl;
    cout << "Shortest time: " << distance[nearestHospital] << " minutes\n";
    cout << "Optimal path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

int main() {
    int choice;
    while (true) {
        cout << "\n1. Find quickest hospital route\n";
        cout << "2. Update road travel time\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            string source;
            cout << "Ambulance current location: ";
            cin >> source;
            if (graph.count(source)) findNearestHospital(source);
            else cout << "Invalid junction.\n";
        } else if (choice == 2) {
            string start, end;
            int newTime;
            cout << "First junction: ";
            cin >> start;
            cout << "Second junction: ";
            cin >> end;
            cout << "New travel time (minutes): ";
            cin >> newTime;
            if (graph.count(start) && graph.count(end)) {
                updateRoad(start, end, newTime);
                cout << "Road updated successfully.\n";
            } else cout << "Invalid junction.\n";
        } else if (choice == 3) {
            cout << "System closed.\n";
            break;
        } else cout << "Invalid option.\n";
    }
    return 0;
}