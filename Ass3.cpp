
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
using namespace std;

struct Item {
    string name;
    double weight, value;

    double ratio() const {
        return value / weight;
    }
};

bool compareItems(const Item& a, const Item& b) {
    return a.ratio() > b.ratio();
}

int main() {
    int n;
    double capacity;

    cout << "Enter number of relief items: ";
    cin >> n;

    if(n <= 0) {
        cout << "Invalid number of items\n";
        return 1;
    }

    vector<Item> items(n);

    for(int i=0; i<n; i++) {
        cout << "\nItem " << i+1 << " name: ";
        cin >> items[i].name;

        cout << "Weight (kg): ";
        cin >> items[i].weight;

        cout << "Utility value: ";
        cin >> items[i].value;

        if(items[i].weight <= 0 || items[i].value < 0) {
            cout << "Invalid weight or utility value\n";
            return 1;
        }
    }

    cout << "\nEnter boat capacity (kg): ";
    cin >> capacity;

    if(capacity < 0) {
        cout << "Invalid capacity\n";
        return 1;
    }

    sort(items.begin(), items.end(), compareItems);

    double totalValue = 0.0;
    double totalWeight = 0.0;

    cout << fixed << setprecision(2);
    cout << "\nSelected supplies:\n";

    for(const Item& item : items) {
        if(capacity <= 0)
            break;

        if(item.weight <= capacity) {
            cout << item.name
                 << ": 100% selected, "
                 << item.weight << " kg\n";

            capacity -= item.weight;
            totalWeight += item.weight;
            totalValue += item.value;
        } else {
            double fraction = capacity / item.weight;

            cout << item.name << ": "
                 << fraction * 100
                 << "% selected, "
                 << capacity << " kg\n";

            totalWeight += capacity;
            totalValue += item.value * fraction;
            capacity = 0;
        }
    }

    cout << "\nTotal weight carried = "
         << totalWeight << " kg\n";

    cout << "Maximum utility value = "
         << totalValue << "\n";

    return 0;
}
