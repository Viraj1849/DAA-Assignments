#include <iostream>
using namespace std;

int graph[100][100];
int color[100];
int rooms[100];
int n, maxRooms;

bool isSafe(int course, int slot) {
    for (int i = 0; i < n; i++) {
        if (graph[course][i] == 1 && color[i] == slot)
            return false;
    }

    if (rooms[slot] >= maxRooms)
        return false;

    return true;
}

bool graphColoring(int course, int totalSlots) {
    if (course == n)
        return true;

    for (int slot = 0; slot < totalSlots; slot++) {
        if (isSafe(course, slot)) {
            color[course] = slot;
            rooms[slot]++;

            if (graphColoring(course + 1, totalSlots))
                return true;

            color[course] = -1;
            rooms[slot]--;
        }
    }

    return false;
}

int main() {
    int edges;

    cout << "Enter number of courses: ";
    cin >> n;
    cout << "Enter number of rooms available in each slot: ";
    cin >> maxRooms;

    for (int i = 0; i < n; i++) {
        color[i] = -1;
        rooms[i] = 0;
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;
    }

    cout << "Enter number of conflicts (edges): ";
    cin >> edges;
    cout << "Enter course pairs having common students:\n";

    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    for (int slots = 1; slots <= n; slots++) {
        for (int i = 0; i < n; i++) {
            color[i] = -1;
            rooms[i] = 0;
        }

        if (graphColoring(0, slots)) {
            cout << "\n----- EXAM TIMETABLE -----\n";
            for (int slot = 0; slot < slots; slot++) {
                cout << "\nSlot " << slot + 1 << ":\n";
                int roomNumber = 1;

                for (int i = 0; i < n; i++) {
                    if (color[i] == slot) {
                        cout << "Course " << i
                             << " -> Room " << roomNumber << endl;
                        roomNumber++;
                    }
                }
            }

            cout << "\nMinimum Exam Slots Required = "
                 << slots << endl;
            return 0;
        }
    }

    cout << "\nNo valid timetable possible.\n";
    return 0;
}